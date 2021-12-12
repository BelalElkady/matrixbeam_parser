// DataParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/writer.h"
#include "TimestampCapture.h"
#include <cstdio>

int main()
{
    using namespace rapidjson;

    FILE* fp = fopen("generated.json", "rb"); // non-Windows use "r"
    vector<ObjectCapture> ObjCaptureVector;

    char readBuffer[16384];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document doc;
    doc.ParseStream(is);


    assert(doc.IsArray());

    //assert(doc[0].IsObject());
    
    /*loop over the whole JSON array*/
    for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr) {

        const Value& obj = *itr;
        /*loop over each and every object which has time and array of object */
        for (Value::ConstMemberIterator it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {
       
           if (it->value.IsArray()&&!it->value.Empty()) {
               const Value& obj1 = it->value;
               int NoOfObjects = 0;
               /*loop over "Objects" array */
               for (Value::ConstValueIterator itre = obj1.Begin(); itre != obj1.End(); ++itre) {
                   NoOfObjects = obj1.Size();
                   
                   std::cout << "NoOfObjects: " << NoOfObjects << std::endl;

                   const Value& obj2 = *itre;
                   /*loop over each object elements */
                   for (Value::ConstMemberIterator it = obj2.MemberBegin(); it != obj2.MemberEnd(); ++it) {
                       ObjectCapture ObjCapture;
                       string name = it->name.GetString();
                       if (name.compare("id") == 0) {

                           ObjCapture.setId(it->value.GetInt());
                           
                       }else if (name.compare("set") == 0) {

                           ObjCapture.setSet(it->value.GetInt());

                       }
                       else if (name.compare("position") == 0) {
                           int pos[3];
                           for (int i = 0; i < 3; i++) {
                               pos[i] = it->value[i].GetInt();
                          }

                       
                           ObjCapture.updatePosition(pos);
                                

                       }
                       else if (name.compare("category") == 0) {

                           ObjCapture.setCategory(it->value.GetString());
                       
                       }
                       else if (name.compare("subcategory") == 0) {

                           ObjCapture.setSubcategory(it->value.GetString());

                       }
                       else if (name.compare("name") == 0) {

                           ObjCapture.setName(it->value.GetString());

                       }
                       else if (name.compare("place") == 0) {

                           ObjCapture.setPlace(it->value.GetString());

                       }
                       else if (name.compare("motion") == 0) {

                           ObjCapture.setMotion(it->value.GetFloat());

                       }
                       else {

                       }
                       ObjCaptureVector.push_back(ObjCapture);
                     
                   }

                   /* Here pass the vector and check the data */
              
               }

            }

        }
    }
  
    fclose(fp);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
