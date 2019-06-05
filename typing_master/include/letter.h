#ifndef _LETTER_H_
#define _LETTER_H_

//klasa letter reprezentuje spadajacy obiekt
//posiada trzy atrybuty: znak oraz pozycje w plasczyznie XY
class Letter
{
public:
    Letter(char letter, int PosX, int PosY);
    char letter;
    int PosX;
    int PosY;
    ~Letter();
};

#endif