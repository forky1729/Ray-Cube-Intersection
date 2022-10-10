#include <iostream>


// структуры =======================================================================

struct vec3
{
    float x, y, z;
};


struct ray              //прямая
{
    vec3 origin;        //начальная точка
    vec3 direction;     //направляющий вектор прямой
};


struct cube             //кубик
{
    vec3 center;        //центр куба
    vec3 diagonal;      //направляющий вектор одной из полудиагоналей куба
};


struct result           //результат
{
    vec3 res1;
    vec3 res2;
};


struct Plane            //плоскость
{
    vec3 point;         //точка плоскости
    vec3 norm;          //вектор нормали
};


struct RayPlane         //точка пересечения прямой и плоскости
{
    float t;
    vec3 RayPlane;
};


// функции ===========================================================================

vec3 vectorProduct (vec3 vec1, vec3 vec2)                   //векторное произведение
{
    vec3 res;
    res.x =    vec1.y * vec2.z - vec1.z * vec2.y;
    res.y = -(vec1.x * vec2.z - vec1.z * vec2.x);
    res.z =    vec1.x * vec2.y - vec1.y * vec2.x;
    return res;
}


vec3 operator- (vec3 p1, vec3 p2)                            //координаты вектора из двух точек
{
    vec3 vec;
    vec.x = p2.x-p1.x;
    vec.y = p2.y-p1.y;
    vec.z = p2.z-p1.z;
    return vec;
}


vec3 operator+ (vec3 vec1, vec3 vec2)                       //сложение векторов
{
    vec3 vec;
    vec.x = vec1.x + vec2.x;
    vec.y = vec1.y + vec2.y;
    vec.z = vec1.z + vec2.z;
    return vec;
}


float operator* (vec3 vec1, vec3 vec2)                      //скалярное произведение
{
    float res;
    res = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    return res;
}


RayPlane rayPlaneIntersection (ray Ray, Plane Plane)
{
    vec3 res0;
    float d;
    d = -1*(Plane.norm*Plane.point);
    float t;
    t = -1*(Ray.origin*Plane.norm + d) / (Ray.direction*Plane.norm);
    res0.x = Ray.origin.x + t*Ray.direction.x;
    res0.y = Ray.origin.y + t*Ray.direction.y;
    res0.z = Ray.origin.z + t*Ray.direction.z;
    return {t, res0};
}


result RayCubeIntersection (ray ray, cube cube)
{
    result result;

    //координаты вершин куба
    vec3 A = {cube.center.x + cube.diagonal.x, cube.center.y + cube.diagonal.y, cube.center.z + cube.diagonal.z};
    vec3 Cs = {cube.center.x - cube.diagonal.x, cube.center.y - cube.diagonal.y, cube.center.z - cube.diagonal.z};
    vec3 B = {cube.center.x + cube.diagonal.x, cube.center.y - cube.diagonal.y, cube.center.z + cube.diagonal.z};
    vec3 Ds = {cube.center.x - cube.diagonal.x, cube.center.y + cube.diagonal.y, cube.center.z - cube.diagonal.z};
    vec3 D = {cube.center.x - cube.diagonal.x, cube.center.y + cube.diagonal.y, cube.center.z + cube.diagonal.z};
    vec3 Bs = {cube.center.x + cube.diagonal.x, cube.center.y - cube.diagonal.y, cube.center.z - cube.diagonal.z};

    //вектора нормали
    vec3 n1, n2, n3;
    n1 = vectorProduct(A-B, A-D);
    n2 = vectorProduct(B-A, B-Bs);
    n3 = vectorProduct(D-A, D-D);
    

    //плоскости граней куба
    Plane ABD = {A, n1};
    Plane ABBs = {B, n2};
    Plane ADDs = {D, n3};
    Plane BBsCs = {Bs, n3};
    Plane DDsCs = {Ds, n2};
    Plane BsCsDs = {Cs, n1};


    //точки пересечения луча и плоскостей граней куба
    RayPlane vABD = rayPlaneIntersection(ray, ABD);
    RayPlane vABBs = rayPlaneIntersection(ray, ABBs);
    RayPlane vADDs = rayPlaneIntersection(ray, ADDs);
    RayPlane vBBsCs = rayPlaneIntersection(ray, BBsCs);
    RayPlane vDDsCs = rayPlaneIntersection(ray, DDsCs);
    RayPlane vBsCsDs = rayPlaneIntersection(ray, BsCsDs);


    //нахождение точек пересечения с кубом
    RayPlane cross_max[3];
    RayPlane cross_min[3];


    float t1, t2;


    if (vABD.t > vBsCsDs.t)
    {
        cross_max[0] = vABD;
        cross_min[0] = vBsCsDs;
    }
    else
    {
        cross_max[0] = vBsCsDs;
        cross_min[0] = vABD;
    }

    if (vABBs.t > vDDsCs.t)
    {
        cross_max[1] = vABBs;
        cross_min[1] = vDDsCs;
    }
    else
    {
        cross_max[1] = vDDsCs, cross_min[1] = vABBs;
    }

    if (vBBsCs.t > vADDs.t)
    {
        cross_max[2] = vBBsCs;
        cross_min[2] = vADDs;
    }
    else
    {
        cross_max[2] = vADDs;
        cross_min[2] = vBBsCs;
    }
    

    if (cross_max[0].t < cross_max[1].t)
    {
        if (cross_max[0].t < cross_max[2].t)
        {
            result.res1 = cross_max[0].RayPlane;
            t1 = cross_max[0].t;
        }
        else
        {
            result.res1 = cross_max[2].RayPlane;
            t1 = cross_max[2].t;
        }
    }
    else
    {
        if (cross_max[1].t < cross_max[2].t)
        {
            result.res1 = cross_max[1].RayPlane;
            t1 = cross_max[1].t;
        }
        else
        {
            result.res1 = cross_max[2].RayPlane;
            t1 = cross_max[2].t;
        }
    }
    

    if (cross_min[0].t > cross_min[1].t)
    {
        if (cross_min[0].t > cross_min[2].t)
        {
            result.res2 = cross_min[0].RayPlane;
            t2 = cross_min[0].t;
        }
        else
        {
            result.res2 = cross_min[2].RayPlane;
            t2 = cross_min[2].t;
        }
    }
    else
    {
        if (cross_min[1].t > cross_min[2].t)
        {
            result.res2 = cross_min[1].RayPlane;
            t2 = cross_min[1].t;
        }
        else
        {
            result.res2 = cross_min[2].RayPlane;
            t2 = cross_min[2].t;
        }
    }
    

    if (t2<t1)
    {
        return result = {{111,0,0}, {0,0,0}};
    }
    else
    {
        return result;
    }
}



int main()
{
    vec3 v1, v2, v3, v4;
    std::cout<<"Начальная точка луча ";
    std::cin>>v1.x>>v1.y>>v1.z;
    std::cout<<"Направление луча ";
    std::cin>>v2.x>>v2.y>>v2.z;
    std::cout<<"Центр куба ";
    std::cin>>v3.x>>v3.y>>v3.z;
    std::cout<<"Полудиагональ куба ";
    std::cin>>v4.x>>v4.y>>v4.z;
    ray ray = {v1,v2};
    cube cube = {v3,v4};
    std::cout<<RayCubeIntersection(ray, cube).res1.x<<" "<<RayCubeIntersection(ray, cube).res1.y<<" "<<RayCubeIntersection(ray, cube).res1.z<<std::endl;
    std::cout<<RayCubeIntersection(ray, cube).res2.x<<" "<<RayCubeIntersection(ray, cube).res2.y<<" "<<RayCubeIntersection(ray, cube).res2.z<<std::endl;
    return 0;
}




/*

   C__ __ __ __ __ __ _ D
   /|                 /|
  / |                / |
 /__|__ __ __ __ __ /  |
| B |               |A |
|   |               |  |
|   |               |  |
|   |               |  |
| Cs|_ __ __ __ __ _|__| Ds
|  /                |  /
| /                 | /
|/_ __ __ __ __ __ _|/
Bs                  As


*/
