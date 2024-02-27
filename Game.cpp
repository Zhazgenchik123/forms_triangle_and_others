#include <iostream>
#include <cstdlib>
#include <cmath>
#define M_PI    3.14159265358979323846264338

struct Angle {
    double ang1;
    double ang2;
    double ang3;
};
class form {
public:
    double cordinateX;
    double cordinateY;
    virtual bool locate(double x, double y)=0;
};
class circle : public form {
public:
    double radius;
    circle(double x, double y, double r) :radius(r){
        
        this->cordinateX = x;
        this->cordinateY = y;
    }
   
    virtual bool locate(double x, double y) override {
        double diff_x = abs(x - cordinateX);
        double diff_y = abs(y - cordinateY);
       return radius * radius > diff_x * diff_x + diff_y * diff_y; 
        
    }
};
class square :public form {
public:
    double side;
    square(double x, double y, double s) :side(s) {
        this->cordinateX = x;
        this->cordinateY = y;
    }
    virtual bool locate(double x, double y) override {
        double diff_x = abs(x - cordinateX);
        double diff_y = abs(y - cordinateY);
        return diff_x < side && diff_y < side;
    }
};
class triangle :public form {
public:
    
    Angle ang1,ang2,ang3;
    double x1, y1, x2, y2, x3, y3;
    double vector1[2], vector2[2], vector3[2];// создаем вектора
    double angle1_2, angle2_3;// создаем углы по моей догадке хватит
    //и двух потому что если знаешь 2 то знаешь и 3 (только для треугольника)
    bool angle_indication1_1;
    bool angle_indication1_2;
    bool angle_indication2_1;
    bool angle_indication2_2;
    double findoneAngle(double v1[2], double v2[2]) {
        double result =
            acos((v1[0] * v2[0] + v1[1] * v2[1]) /
                ((pow(v1[0] * v1[0] + v1[1] * v1[1], 0.5)
                    * pow(v2[0] * v2[0] + v2[1] * v2[1], 0.5))))
            * 180.0 / M_PI;
        return result;
    }
    triangle(double _x1, double _y1, double _x2, double _y2, double _x3, double _y3) {
       
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        x3 = _x3;
        y3 = _y3;
       
        vector1[0] = (x1 - x2);
        vector1[1] = (y1 - y2);

        vector2[0] = (x2 - x3);
        vector2[1] = (y2 - y3);

        vector3[0] = (x1-x3);
        vector3[1] = (y1-y3);
        
        ang1.ang1 = 180 - findoneAngle(vector1, vector2);
        ang1.ang2 = findoneAngle(vector2, vector3);
        ang1.ang3 = 180 - ang1.ang1 - ang1.ang2;
    }
   
    


    void findAngle(double a1, double b1) {
        
        double x_1, y_1, x_2, y_2, x_3, y_3;   // создаем точки 
      
        x_1 = a1;y_1 = b1;
        x_2 = x2;y_2 = y2;
        x_3 = x3;y_3 = y3;
        
        double vector1_1[2], vector2_2[2], vector3_3[2];// создаем вектора
        double angle1_2, angle2_3;// создаем углы по моей догадке хватит
        //и двух потому что если знаешь 2 то знаешь и 3 (только для треугольника)
        vector1_1[0] = x_1 - x_2;
        vector1_1[1] = y_1 - y_2;

        vector2_2[0] = (x_2 - x_3);
        vector2_2[1] = (y_2 - y_3);

        vector3_3[0] = (x_1-x_3);
        vector3_3[1] = (y_1-y_3);
       
        ang2.ang1 = 180- findoneAngle(vector1_1, vector2_2);
        ang2.ang2 = findoneAngle(vector2_2, vector3_3);
        ang2.ang3 = 180 - ang2.ang1 - ang2.ang2;
    }
    void findAngle2(double a3, double b3) {
    double x_1, y_1, x_2, y_2, x_3, y_3;   // создаем точки 

    x_1 = x1; y_1 = y1;
    x_2 = x2; y_2 = y2;
    x_3 = a3; y_3 = b3;

    double vector1_1_1[2], vector2_2_2[2], vector3_3_3[2];// создаем вектора
    double angle1_2, angle2_3;// создаем углы по моей догадке хватит
    //и двух потому что если знаешь 2 то знаешь и 3 (только для треугольника

    vector1_1_1[0] = x_1 - x_2;
    vector1_1_1[1] = y_1 - y_2;

    vector2_2_2[0] = (x_2 - x_3);
    vector2_2_2[1] = (y_2 - y_3);

    vector3_3_3[0] = (x_1 - x_3);
    vector3_3_3[1] = (y_1 - y_3);
    ang3.ang1 = 180 - findoneAngle(vector1_1_1, vector2_2_2);
    ang3.ang2 = findoneAngle(vector2_2_2, vector3_3_3);
    ang3.ang3 = 180 - ang3.ang1 - ang3.ang2;
}

    void printer() {
        std::cout << ang1.ang1<<"\t" << ang1.ang2 <<"\t"<<ang1.ang3 <<std::endl;
        std::cout << ang2.ang1<<"\t" << ang2.ang2 <<"\t" << ang2.ang3 << std::endl;
        std::cout << ang3.ang1<<"\t" << ang3.ang2 <<"\t" << ang3.ang3 << std::endl;
        
    }
    void startfindingAngle(double a, double b) {
        findAngle(a, b);
        findAngle2(a, b);
    }
   
    virtual bool locate(double x, double y) {
        if (ang1.ang1>ang2.ang1  && ang1.ang2>ang2.ang2)
        {
            return true;
        }
        else {
            return false;
        }
    }
    bool locate2(double x, double y) {
        if (ang3.ang3 < ang1.ang3 && ang1.ang1 > ang3.ang1)
        {
            return true;
        }
        else {
            return false;
        }
    }
};


int main()
{
    triangle tri{ 0, 0, 3, 0, 0, 4 };
    double one = 1;
    double two =1;
    tri.startfindingAngle(one,two);
    tri.printer();
    if (tri.locate(one,two) && tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }
    std::cout << std::endl;
    tri.startfindingAngle(2, 3);
    tri.printer();
    if (tri.locate(one, two)&& tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }
    std::cout << std::endl;
    tri.startfindingAngle(-1, 2);
    tri.printer();
    if (tri.locate(one, two)&& tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }
    std::cout << std::endl;
    tri.startfindingAngle(1, -1);
    tri.printer();
    if (tri.locate(one, two) && tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }
    std::cout << std::endl;
    tri.startfindingAngle(1, 2);
    tri.printer();
    if (tri.locate(one, two) && tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }

    std::cout << std::endl;
    tri.startfindingAngle(2, -1);
    tri.printer();
    if (tri.locate(one, two) && tri.locate2(one, two))
    {
        std::cout << "yes";

    }
    else {
        std::cout << "no";
    }
   
}

