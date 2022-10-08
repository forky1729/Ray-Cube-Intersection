#include <iostream>


//куб

struct vec3
{
    float x, y, z;
};

struct ray          //прямая
{
    vec3 origin;    //начальная точка
    vec3 direction; //направляющий вектор прямой
};

struct cube         //кубик
{
    vec3 center;    //центр куба
    vec3 diagonal;  //направляющий вектор одной из полудиагоналей куба
};

struct result       //результат
{
    vec3 res1;
    vec3 res2;
};

struct Plane       //плоскость
{
    vec3 point;    //точка плоскости
    vec3 norm;     //вектор нормали
};


struct RayPlane
{
    double t;
    vec3 RayPlane;
};


vec3 vectorProduct (vec3 vec1, vec3 vec2)
{
    vec3 res;
    res.x = vec1.y * vec2.z - vec1.z * vec2.y;
    res.y = -(vec1.x * vec2.z - vec1.z * vec2.x);
    res.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return res;
}



RayPlane rayPlaneIntersection (ray Ray, Plane Plane)
{
    vec3 res0;
    double d;
    d = -1*(Plane.norm.x*Plane.point.x + Plane.norm.y*Plane.point.y + Plane.norm.z*Plane.point.z);
    double t;
    t = -1*(Ray.origin.x*Plane.norm.x + Ray.origin.y*Plane.norm.y + Ray.origin.z*Plane.norm.z + d) / (Ray.direction.x*Plane.norm.x + Ray.direction.y*Plane.norm.y +Ray.direction.z*Plane.norm.z);
    res0.x = Ray.origin.x + t*Ray.direction.x;
    res0.y = Ray.origin.y + t*Ray.direction.y;
    res0.z = Ray.origin.z + t*Ray.direction.z;
    return {t, res0};
}



vec3 twoPoints(vec3 p1, vec3 p2)
{
    vec3 vec;
    vec.x = p2.x-p1.x;
    vec.y = p2.y-p1.y;
    return vec;
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


    //плоскости граней куба
    vec3 AB, AD, BA, BBs, DA, DDs, BsB, BsCs, DsD, DsCs, CsBs, CsDs;
    Plane ABD = {A, vectorProduct(twoPoints(A,B), twoPoints(A,D))};
    Plane ABBs = {B, vectorProduct(twoPoints(B,A), twoPoints(B,Bs))};
    Plane ADDs = {D, vectorProduct(twoPoints(D,A), twoPoints(D,Ds))};
    Plane BBsCs = {Bs, vectorProduct(twoPoints(Bs,B), twoPoints(Bs,Cs))};
    Plane DDsCs = {Ds, vectorProduct(twoPoints(Ds,D), twoPoints(Ds,Cs))};
    Plane BsCsDs = {Cs, vectorProduct(twoPoints(Cs,Bs), twoPoints(Cs,Ds))};


    //точки пересечения луча и плоскостей граней куба
    RayPlane vABD = rayPlaneIntersection(ray, ABD);
    RayPlane vABBs = rayPlaneIntersection(ray, ABBs);
    RayPlane vADDs = rayPlaneIntersection(ray, ADDs);
    RayPlane vBBsCs = rayPlaneIntersection(ray, BBsCs);
    RayPlane vDDsCs = rayPlaneIntersection(ray, DDsCs);
    RayPlane vBsCsDs = rayPlaneIntersection(ray, BsCsDs);


    //нахождение точек пересечения с кубом
    RayPlane cross[] = {vABD, vABBs, vADDs, vBBsCs, vDDsCs, vBsCsDs};
    RayPlane temp;
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 5 - i; ++j)
        {
            if (cross[j].t > cross[j+1].t) 
            {
                temp = cross[j];
                cross[j] = cross[j+1];
                cross[j+1] = temp;
            }
        }
    }
    result = {cross[2].RayPlane, cross[3].RayPlane};
    return result;
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
