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



vec3 vectorProduct (vec3 vec1, vec3 vec2)
{
    vec3 res;
    res.x = vec1.y * vec2.z - vec1.z * vec2.y;
    res.y = -(vec1.x * vec2.z - vec1.z * vec2.x);
    res.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return res;
}



vec3 rayPlaneIntersection (ray Ray, Plane Plane)
{
    vec3 res0;
    double d;
    d = -1*(Plane.norm.x*Plane.point.x + Plane.norm.y*Plane.point.y + Plane.norm.z*Plane.point.z);
    double t;
    t = -1*(Ray.origin.x*Plane.norm.x + Ray.origin.y*Plane.norm.y + Ray.origin.z*Plane.norm.z + d) / (Ray.direction.x*Plane.norm.x + Ray.direction.y*Plane.norm.y +Ray.direction.z*Plane.norm.z);
    res0.x = Ray.origin.x + t*Ray.direction.x;
    res0.y = Ray.origin.y + t*Ray.direction.y;
    res0.z = Ray.origin.z + t*Ray.direction.z;
    return res0;
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
    Plane ABD = {A, vectorProduct(AB = {B.x-A.x, B.y-A.y, B.z-A.z}, AD = {D.x-A.x, D.y-A.y, D.z-A.z})};
    Plane ABBs = {B, vectorProduct(BA = {A.x-B.x, A.y-B.y, A.z-B.z}, BBs = {Bs.x-B.x, Bs.y-B.y, Bs.z-B.z})};
    Plane ADDs = {D, vectorProduct(DA = {A.x-D.x, A.y-D.y, A.z-D.z}, DDs = {Ds.x-D.x, Ds.y-D.y, Ds.z-D.z})};
    Plane BBsCs = {Bs, vectorProduct(BsB = {B.x-Bs.x, B.y-Bs.y, B.z-Bs.z}, BsCs = {Cs.x-Bs.x, Cs.y-Bs.y, Cs.z-Bs.z})};
    Plane DDsCs = {Ds, vectorProduct(DsD = {D.x-Ds.x, D.y-Ds.y, D.z-Ds.z}, DsCs = {Cs.x-Ds.x, Cs.y-Ds.y, Cs.z-Ds.z})};
    Plane BsCsDs = {Cs, vectorProduct(CsBs = {Bs.x-Cs.x, Bs.y-Cs.y, Bs.z-Cs.z}, CsDs = {Ds.x-Cs.x, Ds.y-Cs.y, Ds.z-Cs.z})};


    //точки пересечения луча и плоскостей граней куба
    vec3 vABD = rayPlaneIntersection(ray, ABD);
    vec3 vABBs = rayPlaneIntersection(ray, ABBs);
    vec3 vADDs = rayPlaneIntersection(ray, ADDs);
    vec3 vBBsCs = rayPlaneIntersection(ray, BBsCs);
    vec3 vDDsCs = rayPlaneIntersection(ray, DDsCs);
    vec3 vBsCsDs = rayPlaneIntersection(ray, BsCsDs);


    //нахождение точек пересечения с кубом
    vec3 cross[] = {vABD, vABBs, vADDs, vBBsCs, vDDsCs, vBsCsDs};
    vec3 temp;
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 5 - i; ++j)
        {
            if (cross[j].x > cross[j+1].x) 
            {
                temp = cross[j];
                cross[j] = cross[j+1];
                cross[j+1] = temp;
            }
        }
    }
    result = {cross[2], cross[3]};
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
