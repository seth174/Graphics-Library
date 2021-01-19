#include<iostream>
using namespace std;
#include "Model.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Vector2.h"
#include<stdlib.h>


Model::Model()
{
    triangles.clear();
}

 void Model :: transform(Matrix4 m) {
     
     for(int i =0; i<numTriangles(); i++) {
        if(triangles[i].shouldDraw) {
            triangles[i].transform(m); 
        }
     }
 }

int Model::numTriangles()
{
    return triangles.size();
}

Triangle3D Model::operator[](int i)
{
    Triangle3D temp;
    temp = triangles[i];
    return temp;
}

void Model :: readFromOBJFile(string filepath, Color pFillColor) {
    vector<Vector4> vertices; 
    

    ifstream myFile(filepath); 

    if (myFile.is_open()) {
        string line; 
        string myWord; 
        while(getline(myFile, line)) {
            istringstream s(line);
            vector<string> words;
            while(getline(s, myWord, ' ')) {
                words.push_back(myWord);
            } 
            if(words[0] == "v") {
                float v1 = atof(words[1].c_str()); 
                float v2 = atof(words[2].c_str()); 
                float v3 = atof(words[3].c_str()); 
                vertices.push_back(Vector4(v1,v2,v3,1.0)); 
            }
            else if(words[0] == "f") {
                if (words.size() == 4) {
                    string s = words[1];
                    int temp = atoi(s.c_str());
                    Vector4 v1 = vertices.at(temp - 1); 
                    
                    string s2 = words[2];
                    int temp2 = atoi(s2.c_str());
                    Vector4 v2 = vertices.at(temp2 - 1); 

                    string s3 = words[3];
                    int temp3 = atoi(s3.c_str());
                    Vector4 v3 = vertices.at(temp3 - 1); 

                    this->triangles.push_back(Triangle3D(v1, v2, v3, pFillColor, pFillColor, pFillColor)); 
                    
                
                }

                else {
                    string s = words[1];
                    int temp = atoi(s.c_str());
                    Vector4 v1 = vertices.at(temp - 1); 
                    
                    string s2 = words[2];
                    int temp2 = atoi(s2.c_str());
                    Vector4 v2 = vertices.at(temp2 - 1); 

                    string s3 = words[3];
                    int temp3 = atoi(s3.c_str());
                    Vector4 v3 = vertices.at(temp3 - 1); 

                    string s4 = words[4];
                    int temp4 = atoi(s4.c_str());
                    Vector4 v4 = vertices.at(temp4 - 1); 

                    this->triangles.push_back(Triangle3D(v1, v2, v3, pFillColor, pFillColor, pFillColor));

                    this->triangles.push_back(Triangle3D(v1, v3, v4, pFillColor, pFillColor, pFillColor));
                    
                }
            }
            }
            
             
        }
    }

    void Model :: test(){
        for(int i = 0; i < numTriangles(); i++)
        {
            cout<<triangles[i].v1.xComponent<<endl;
            cout<<triangles[i].v1.yComponent<<endl;
            cout<<triangles[i].v1.zComponent<<endl;
            cout<<triangles[i].v1.w<<endl;
        }

     }

    void Model:: performBackfaceCulling(Vector4 eye, Vector4 spot)
     {
        Vector4 look = spot - eye;
        for(int i = 0; i < numTriangles(); i++)
        {
            Vector4 a = triangles[i].v3 - triangles[i].v2;
            Vector4 b = triangles[i].v1 - triangles[i].v2;
            Vector4 n = a.cross(b);
            n.normalize();
            if(n.dot(look) <= 0)
            {
                triangles[i].shouldDraw = false;
            }
        }
     }

    void Model :: homogenize() {
        //I commented out the if statement because something weird was happening when I ran it.
        //Could you let me know why those if statements dont work
        for(int i =0; i<numTriangles(); i++) {

            //if((triangles[i].v1.xComponent <= abs(triangles[i].v1.w)) && (triangles[i].v1.yComponent <= abs(triangles[i].v1.w))
           //&& (triangles[i].v1.zComponent <= abs(triangles[i].v1.w)))
            //{
                triangles[i].v1.xComponent = triangles[i].v1.xComponent / triangles[i].v1.w;
                triangles[i].v1.yComponent = triangles[i].v1.yComponent / triangles[i].v1.w;
                triangles[i].v1.zComponent = triangles[i].v1.zComponent / triangles[i].v1.w;
                triangles[i].v1.w = triangles[i].v1.w / triangles[i].v1.w;
            //}

           //if((triangles[i].v2.xComponent <= abs(triangles[i].v2.w)) && (triangles[i].v2.yComponent <= abs(triangles[i].v2.w))
            //&& (triangles[i].v2.zComponent <= abs(triangles[i].v2.w)))
            //{
                triangles[i].v2.xComponent = triangles[i].v2.xComponent / triangles[i].v2.w;
                triangles[i].v2.yComponent = triangles[i].v2.yComponent / triangles[i].v2.w;
                triangles[i].v2.zComponent = triangles[i].v2.zComponent / triangles[i].v2.w;
                triangles[i].v2.w = triangles[i].v2.w / triangles[i].v2.w;
            //}

            //if((triangles[i].v3.xComponent <= abs(triangles[i].v3.w)) && (triangles[i].v3.yComponent <= abs(triangles[i].v3.w))
            //&& (triangles[i].v3.zComponent <= abs(triangles[i].v3.w)))  
            //{
                triangles[i].v3.xComponent = triangles[i].v3.xComponent / triangles[i].v3.w;
                triangles[i].v3.yComponent = triangles[i].v3.yComponent / triangles[i].v3.w;
                triangles[i].v3.zComponent = triangles[i].v3.zComponent / triangles[i].v3.w;
                triangles[i].v3.w = triangles[i].v3.w / triangles[i].v3.w;
            //}          
     }



    } 




