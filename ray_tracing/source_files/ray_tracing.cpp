#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <glut.h>
#include <GL/gl.h>
#include <fstream>
#include <string>
using namespace std;
#pragma region zmienne
typedef float punkt[3];
//g³êbokoœæ rekurencji
#define MAX 1000
int step = 0;
//rozmiary okna
int horizontal = 0;
int vertical = 0;
float viewport_size = 18.0;
//punkt pocz¹tkowy
punkt starting_point;
punkt starting_directions = { 0.0, 0.0, -1.0 };
//pomocnicze struktury do pracy z typem definiowanyn
struct punktSphereStruct {
	punkt pos;
	int sphere;
	int light;
	int status;
};
struct punktStruct {
	punkt pos;
};
//parametry œwiate³
float light_position[5][3];
float light_specular[5][3];
float light_diffuse[5][3];
float light_ambient[5][3];
//kolor wype³nienia t³a
float background_color[3];
//parametry rozproszenia globalnego
float global_a[3];
//parametry sfer
float sphere_radius[9];
float sphere_position[9][3];
float sphere_specular[9][3];
float sphere_diffuse[9][3];
float sphere_ambient[9][3];
float sphere_shiness[9];
//bie¿¹cy kolor piksela - struktura GLubyte przechowuje info
GLubyte pixel[1][1][3];
#pragma endregion
#pragma region f_pomocnicze
//funkcja licz¹ca iloczyn skalarny dwóch wektorów
float dotProduct(punkt p, punkt q)
{
	return (p[0] * q[0] + p[1] * q[1] + p[2] * q[2]);
}
//pomocnicza funckja licz¹ca d³ugoœæ wektora
float vector_length(punktStruct v)
{
	return (v.pos[0] * v.pos[0] + v.pos[1] * v.pos[1] + v.pos[2] * v.pos[2]);
}
#pragma endregion
#pragma region f_normalizacyjne
//funkcja normalizuj¹ca podany wektor v -- dzielenie wektora przez jego d³ugoœæ
punktStruct Normalization(punkt v)
{
	//wktor znormalizowany
	//inicjacja dla bezpieczeñstwa
	punktStruct normalized_vec;
	normalized_vec.pos[0] = 0.0;
	normalized_vec.pos[1] = 0.0;
	normalized_vec.pos[2] = 0.0;
	//algorytm wg instrukcji laboratoryjnej
	float d = 0.0;
	int i;
	for (i = 0; i < 3; i++)
		d += v[i] * v[i];
	d = sqrt(d);
	if (d > 0.0)
		for (i = 0; i < 3; i++)
			normalized_vec.pos[i] = v[i] / (d*1.0);
	
	return normalized_vec;
}
//funkcja licz¹ca wektor normalny do powierzchni w podanym punkcie - q dla obiektu o numerze sphere
punktStruct Normal(punkt v, int sphere_number)
{
	punktStruct normal_vec;
	for (int i = 0; i < 3; i++)
	{
		normal_vec.pos[i] = (v[i] - sphere_position[sphere_number][i]) / sphere_radius[sphere_number];
	}
	return normal_vec;
}
#pragma endregion
#pragma region f_glowne
//funkcja licz¹ca wektor odbicia
punktStruct Reflect(punkt p, punkt q, punkt n)
{
	punktStruct reflect_vec; //wektor odbicia
	punkt direct_vec;		 //wektor kierunkowy
	direct_vec[0] = p[0] - q[0];
	direct_vec[1] = p[1] - q[1];
	direct_vec[2] = p[2] - q[2];
	//pomocnicza konwersja
	punktStruct temp = Normalization(direct_vec);
	direct_vec[0] = temp.pos[0];
	direct_vec[1] = temp.pos[1];
	direct_vec[2] = temp.pos[2];
	//obliczenie iloczynu skalaranego w celu podstawienia wartoœci do wzoru
	float r_dot_d;
	r_dot_d = dotProduct(direct_vec, n);
	//obliczenie wektora promienia odbitego
	reflect_vec.pos[0] = 2 * (r_dot_d)* n[0] - direct_vec[0];
	reflect_vec.pos[1] = 2 * (r_dot_d)* n[1] - direct_vec[1];
	reflect_vec.pos[2] = 2 * (r_dot_d)* n[2] - direct_vec[2];
	//je¿eli wektor nie jest jednostkowy, to nale¿y fo wpierw znormalizowaæ
	if (vector_length(reflect_vec) > 1.0)
		return Normalization(reflect_vec.pos);
	else return reflect_vec;
}
//funkcja wyznaczaj¹ca punkt przeciêcia (pierwszy na drodze)
//œledzonego promienia oraz obiektu (tu sfery/œwiat³a/pró¿ni) w który promieñ trafia
punktSphereStruct Intersect(punkt p, punkt v)
{
	//utworzenie obiektu definuj¹cego punkt przeciêcia
	//struktura zawiera wszytsko co jednoznacznie pozwala
	//taki punkt wyœwietliæ w oknie
	punktSphereStruct intersected_vec;
	intersected_vec.pos[0] = 0.0;
	intersected_vec.pos[1] = 0.0;
	intersected_vec.pos[2] = 0.0;
	intersected_vec.sphere = 0;
	intersected_vec.light = 0;
	intersected_vec.status = 0;
	//zmienne pomocnicze do obliczeñ
	float x, y, z;
	//okreœlenie czy promien trafi³ w Ÿród³o
	for (int i = 0; i < 5; i++)
	{
		//wyliczenie wektora kierunkowego punkt -> Ÿród³o œwiat³
		x = light_position[i][0] - p[0];
		y = light_position[i][1] - p[1];
		z = light_position[i][2] - p[2];
		//sprawdzenie wektor powy¿szy jest to¿samy z aktualnym kierunkiem v promienia z punktu p
		if ((x / v[0]) == (y / v[1]) && (y / v[1]) == (z / v[2]))
		{
			//pozycja uderzonego Ÿród³a œwiat³a
			intersected_vec.pos[0] = light_position[i][0];
			intersected_vec.pos[1] = light_position[i][1];
			intersected_vec.pos[2] = light_position[i][2];
			//które dok³adnie Ÿród³o
			intersected_vec.light = i;
			intersected_vec.status = 1;
			return intersected_vec;
		}
	}
	//sprawdzenie czy promieñ trafi³ w któr¹kolwiek ze sfer
	float a, b, c, delta, u;//zestaw zmiennych do obliczeñ testowych
	for (int i = 0; i < 9; i++)
	{
		//przeprowadzane poni¿ej obliczenia przebiegaj¹ zgodnie ze wzorami
		//podanymi w instrukcji laboratoryjnej
		//obliczenie parametrów funkcji kwadratowej
		a = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
		b = 2 * ((p[0] - sphere_position[i][0])*v[0] + (p[1] - sphere_position[i][1])*v[1] + (p[2] - sphere_position[i][2])*v[2]);
		c = (p[0] * p[0] + p[1] * p[1] + p[2] * p[2])
			+ (sphere_position[i][0] * sphere_position[i][0] + sphere_position[i][1] * sphere_position[i][1] + sphere_position[i][2] * sphere_position[i][2])
			- 2 * (p[0] * sphere_position[i][0] + p[1] * sphere_position[i][1] + p[2] * sphere_position[i][2])
			- sphere_radius[i] * sphere_radius[i];
		//wyliczenie delty
		delta = b * b - 4 * a*c;
		//je¿eli delta >= 0 to istniej¹ rozwi¹zanie/rozwi¹zania (nale¿y wzi¹æ to bli¿sze w przypadku istnienia dwóch)
		if (delta >= 0)
		{
			//brane jest rozwi¹zanie bli¿sze [jak wy¿ej opisano]
			u = (-b - sqrt(delta)) / (2 * a);
			if (u > 0)
			{
				//wyliczenie wspó³rzêdnych punktu, gdzie pad³ promieñ
				intersected_vec.pos[0] = p[0] + u * v[0];
				intersected_vec.pos[1] = p[1] + u * v[1];
				intersected_vec.pos[2] = p[2] + u * v[2];
				//z zaznaczeniem, której to sfery dotyczy
				intersected_vec.sphere = i;
				intersected_vec.status = 3;
				break;
			}
		}
	}
	//je¿eli wartoœæ status nie by³a modyfikowana, to znaczy to,
	//¿e promieñ zagin¹³ w przestrzeni tj. nie dotar³ do ¿adnego obiektu
	if (intersected_vec.status == 0)
	{
		intersected_vec.status = 2;
	}
	return intersected_vec;
}
//u¿ywaj¹c modelu Phonga funkcja oblicza oœwietlenie danego punktu
//q - obliczony punkt przeciêcia
//n - wektor normalny do p³aszczyzny w punkcie q
punktStruct Phong(punkt q, punkt n, int sphere)
{
	//wyliczony zostanie kolor punktu
	//inicjalizacja dla bezpieczeñstwa
	punktStruct color;
	color.pos[0] = 0.0;
	color.pos[1] = 0.0;
	color.pos[2] = 0.0;
	//pomocnicze zmienne
	punkt light_vec;        //wektor skierowany ze zwrotem do Ÿród³a
	punkt reflection_vec;   //wektor promienia odbitego
	punkt viewer_vec;		//wektor skierowany do obserwatora
	viewer_vec[0] = 0.0;
	viewer_vec[1] = 0.0;
	viewer_vec[2] = 1.0;
	//odpowiednie iloczny skalarane
	float n_dot_l, v_dot_r;             
	//wspó³czynniki okreœlaj¹ce wp³yw odleg³oœci Ÿród³a œwiat³a na oœwietlenie punktu 
	float a, b, c, scale;
	a = 1.0;
	b = 0.1;
	c = 0.01;
	scale = 1 / (a + b + c);
	//obliczenia oœwietlenia danego punktu musz¹ zostaæ przeprowadzone dla ka¿dego Ÿród³a œwiat³a
	for (int i = 0; i < 5; i++)
	{
		//wyliczenie kierunku wektora z punktu przeciêcia w kierunku Ÿród³a œwiat³a
		light_vec[0] = light_position[i][0] - q[0];
		light_vec[1] = light_position[i][1] - q[1];
		light_vec[2] = light_position[i][2] - q[2];
		//normalizacja wylicoznego wektora
		punktStruct temp = Normalization(light_vec);
		light_vec[0] = temp.pos[0];
		light_vec[1] = temp.pos[1];
		light_vec[2] = temp.pos[2];
		//iloczyn skalarny
		n_dot_l = dotProduct(light_vec, n);
		//wg wzorów z instrukjci laboratoryjnej
		//nastêpuje wyliczenie kierunku odbicia
		reflection_vec[0] = 2 * (n_dot_l)*n[0] - light_vec[0];
		reflection_vec[1] = 2 * (n_dot_l)*n[1] - light_vec[1];
		reflection_vec[2] = 2 * (n_dot_l)*n[2] - light_vec[2];
		//nastêpnie wektor odbica jest tak¿e normalizowany
		//zgodnie z wymogami modelu Phonga, gdzie ka¿dy wektor musi taki byæ
		temp = Normalization(reflection_vec);
		reflection_vec[0] = temp.pos[0];
		reflection_vec[1] = temp.pos[1];
		reflection_vec[2] = temp.pos[2];
		//iloczyn skalarany
		v_dot_r = dotProduct(reflection_vec, viewer_vec);
		//sprawdzenie, czy punkt jest w ogóle widoczny przez obserwatora
		if (v_dot_r < 0)                  
			v_dot_r = 0;
		//sprawdzenie czy punkt na powierzchni sfery jest oœwietlany przez Ÿród³o
		if (n_dot_l > 0)
		{   
			//punkt jest oœwietlany dalej...
			//obliczenia wg modelu Phonga zdefiniowanego w instrukcji laboratoryjnej
			color.pos[0] += scale * (sphere_diffuse[sphere][0] * light_diffuse[i][0] * n_dot_l + sphere_specular[sphere][0] * light_specular[i][0] * pow(double(v_dot_r), double(sphere_shiness[sphere])))
						 + sphere_ambient[sphere][0] * light_ambient[i][0] + sphere_ambient[sphere][0] * global_a[0];
			color.pos[1] += scale * (sphere_diffuse[sphere][1] * light_diffuse[i][1] * n_dot_l + sphere_specular[sphere][1] * light_specular[i][1] * pow(double(v_dot_r), double(sphere_shiness[sphere])))
				         + sphere_ambient[sphere][1] * light_ambient[i][1] + sphere_ambient[sphere][1] * global_a[1];
			color.pos[2] += scale * (sphere_diffuse[sphere][2] * light_diffuse[i][2] * n_dot_l + sphere_specular[sphere][2] * light_specular[i][2] * pow(double(v_dot_r), double(sphere_shiness[sphere])))
				         + sphere_ambient[sphere][2] * light_ambient[i][2] + sphere_ambient[sphere][2] * global_a[2];
		}
		else{
			//w przeciwnym wypadku punkt nie jest oœwietlany
			//jego oœwietlenie wynika wy³¹cznie ze œwiat³a rozproszonego
			color.pos[0] += sphere_ambient[sphere][0] * global_a[0];
			color.pos[1] += sphere_ambient[sphere][1] * global_a[1];
			color.pos[2] += sphere_ambient[sphere][2] * global_a[2];
		}
	}
	return color;
}
//funckja wylicza kolejne punkty przeciêca dla œledzonego promienia
//p - jest Ÿród³em promienia
//v - wskazuje jego kierunek
punktStruct Trace(punkt p, punkt v, int next_step)
{
	punkt q;  //punkt przeciêcia na powierzchni sfery
	punkt n;  //wektor znormalizowany do powierzchni obiektu w punkcie q
	punkt r;  //wektor odbicia
	//zmienne pomocnicze
	int status;				//werykacja w co trafi³ promieñ 
	int light_number;		//numer zrodla swiatla
	int sphere_number;		//numer sfery
	//oœwietlenie lokalne punktu
	punktStruct local;
	local.pos[0] = 0.0;
	local.pos[1] = 0.0;
	local.pos[2] = 0.0;
	//oœwietlenie punktu pochodz¹ce z promieni odbitych
	punktStruct reflected;
	reflected.pos[0] = 0.0;
	reflected.pos[1] = 0.0;
	reflected.pos[2] = 0.0;
	//je¿eli osi¹gniêto po¿¹dan¹ g³êbokoœæ rekurencji dla danego promienia, a on nie trafi³ 
	//w ¿aden obiekt na akualnym etapie, to miejsce to bêdzie kolorwane kolorem t³a
	if (next_step > MAX)
	{
		local.pos[0] += background_color[0];
		local.pos[1] += background_color[1];
		local.pos[2] += background_color[2];
		return local;
	}
	//wyliczenie punktu przeciêcia dla skierowanego promienia
	//wychodz¹cego z punkty p
	//skierowanego wed³ug wektora v
	punktSphereStruct tempSS = Intersect(p, v);
	q[0] = tempSS.pos[0];
	q[1] = tempSS.pos[1];
	q[2] = tempSS.pos[2];
	status = tempSS.status;
	light_number = tempSS.light;
	sphere_number = tempSS.sphere;
	//1 - promieñ trafi³ w zrodlo swiatla
	if (status == 1)
	{
		local.pos[0] += light_specular[light_number][0];
		local.pos[1] += light_specular[light_number][1];
		local.pos[2] += light_specular[light_number][2];
		return local;
	}
	//2 - nic nie zostalo trafione przez promienie
	//piksel przyjmuje wartoœci barwy t³a
	if (status == 2)
	{
		local.pos[0] += background_color[0];
		local.pos[1] += background_color[1];
		local.pos[2] += background_color[2];
		return local;
	}
	//wyliczenie wektora znormalizowanego do powierzchni w punkcie q sfery sphere
	punktStruct tempS = Normal(q, sphere_number);
	n[0] = tempS.pos[0];
	n[1] = tempS.pos[1];
	n[2] = tempS.pos[2];
	//wyliczenie kierunku promienia odbitego od powierzchni obiektu
	tempS = Reflect(p, q, n);
	r[0] = tempS.pos[0];
	r[1] = tempS.pos[1];
	r[2] = tempS.pos[2];
	//oœwietlenie lokalne wyliczane jest z modelu Phonga dla danej sfery w danym punkcie
	local = Phong(q, n, sphere_number);
	//dalsze obliczenia, czyli obliczenia maj¹ce uzysaæ poprzez rekurencjê
	//ca³kowit¹ wartoœæ oœwietlenia w bie¿¹cym punkcie
	reflected = Trace(q, r, next_step + 1);
	//wyliczenie ca³kowitego oœwielenia w punkcie rysowanym
	local.pos[0] += reflected.pos[0];
	local.pos[1] += reflected.pos[1];
	local.pos[2] += reflected.pos[2];
	return local;
};
#pragma endregion
#pragma region f_renderujaca
//funkcja renderuj¹ca obraz sceny
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	//zagnie¿d¿one pêtle przetwarzaj¹ okno
	//przesuwaj¹c siê g³owic¹ od lewej do prawej krawêdzi
	//schodz¹c z górnej do dolnej krawêdzi
	//na bie¿¹co przetwarzany jest - obliczany jest kolor jednego piksela
	float pix_x, pix_y;					//bie¿¹ce wspó³rzêdne piksela
	int horizontal_2 = horizontal / 2;	//po³owa rozmiaru okna
	int vertical_2 = vertical / 2;		//pozwala okreœliæ kierunek przetwarzania okna
	punktStruct color;					//pomocnicza zmmienna przechowuj¹ca kolor piksela - wynikow¹ funkcji œledzenia
	for (int y = vertical_2; y > -vertical_2; y--)
	{
		for (int x = -horizontal_2; x < horizontal_2; x++)
		{
			//obliczenie pozycji kolejnego piksela w kontekœcie okna obserwatora
			pix_x = (float)x / (horizontal / viewport_size);
			pix_y = (float)y / (vertical / viewport_size);
			//punkt - piksel ten ma wspó³rzêdne x y z odpowiednio
			//wg instrukcji laboratoryjnej
			starting_point[0] = pix_x;
			starting_point[1] = pix_y;
			starting_point[2] = viewport_size;
			//wywo³anie dla bie¿¹cego piksela oraz promienia obserwacji funkcji rekurencyjej œledz¹cej jego przebieg
			//tym sposobem otrzymujemy trzy dane do przetworzenia w celu wys=³uskania koloru
			color = Trace(starting_point, starting_directions, step);
			//wyznaczanie koloru piksela
			//wg instrukcji laboratoryjnej
			if (color.pos[0] > 1)
				pixel[0][0][0] = 255;
			else
				pixel[0][0][0] = color.pos[0] * 255;

			if (color.pos[1] > 1)
				pixel[0][0][1] = 255;
			else
				pixel[0][0][1] = color.pos[1] * 255;

			if (color.pos[2] > 1)
				pixel[0][0][2] = 255;
			else
				pixel[0][0][2] = color.pos[2] * 255;
			//inkrementacja pozycji rastrowej
			glRasterPos3f(pix_x, pix_y, 0);
			glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		}
	}
	glFlush();
}
#pragma endregion
#pragma region f_wczytujaca
//funkcja wczytuje dane z pliku tekstowe
//nazwa pliku: scena.txt
void ReadFile(void)  //odczytywanie danych z pliku
{
	fstream infile;
	infile.open("scene.txt");
	string tmp;
	if (infile.is_open() != true)
	{
		cout << "Nie udalo wczytac sie pliku";
	}
	else
	{
		infile >> tmp;
		infile >> horizontal;
		infile >> vertical;
		infile >> tmp;
		for (int i = 0; i < 3; i++) infile >> background_color[i];
		infile >> tmp;
		for (int i = 0; i < 3; i++) infile >> global_a[i];
		for (int i = 0; i < 9; i++)
		{
			infile >> tmp;
			infile >> sphere_radius[i];
			infile >> sphere_position[i][0];
			infile >> sphere_position[i][1];
			infile >> sphere_position[i][2];
			infile >> sphere_specular[i][0];
			infile >> sphere_specular[i][1];
			infile >> sphere_specular[i][2];
			infile >> sphere_diffuse[i][0];
			infile >> sphere_diffuse[i][1];
			infile >> sphere_diffuse[i][2];
			infile >> sphere_ambient[i][0];
			infile >> sphere_ambient[i][1];
			infile >> sphere_ambient[i][2];
			infile >> sphere_shiness[i];
		}
		for (int i = 0; i < 5; i++)
		{
			infile >> tmp;
			infile >> light_position[i][0];
			infile >> light_position[i][1];
			infile >> light_position[i][2];
			infile >> light_specular[i][0];
			infile >> light_specular[i][1];
			infile >> light_specular[i][2];
			infile >> light_diffuse[i][0];
			infile >> light_diffuse[i][1];
			infile >> light_diffuse[i][2];
			infile >> light_ambient[i][0];
			infile >> light_ambient[i][1];
			infile >> light_ambient[i][2];
		}
		infile.close();
	}
}
#pragma endregion
#pragma region f_startowe
//funkcja inicjacyjna
void Myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-viewport_size / 2, viewport_size / 2, -viewport_size / 2, viewport_size / 2, -viewport_size / 2, viewport_size / 2);
	glMatrixMode(GL_MODELVIEW);
}
//funkcja main
int main(void)
{
	ReadFile();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow("MINIPROJEKT - Ray Tracing");
	Myinit();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
#pragma endregion