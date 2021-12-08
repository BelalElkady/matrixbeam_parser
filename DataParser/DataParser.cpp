// DataParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/writer.h"
#include <cstdio>

int main()
{
    using namespace rapidjson;

    FILE* fp = fopen("generated.json", "rb"); // non-Windows use "r"

    char readBuffer[16384];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document doc;
    doc.ParseStream(is);


    assert(doc.IsArray());

    assert(doc[0].IsObject());
    
    


    for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr) {

        const Value& obj = *itr;
        for (Value::ConstMemberIterator it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {
            if (it->value.IsInt()) {
                std::cout << "cdscc" << std::endl;
                std::cout << it->name.GetString() << ": " << it->value.GetInt() << std::endl;
            }

        }
    }
    //std::cout << doc["time"].GetString();

   /* StringBuffer buffer{};
    Writer<StringBuffer> writer{ buffer };
    doc.Accept(writer);

    if (doc.HasParseError())
    {
        std::cout << "Error  : " << doc.GetParseError() << '\n'
            << "Offset : " << doc.GetErrorOffset() << '\n';
        return EXIT_FAILURE;
    }

    const std::string jsonStr{ buffer.GetString() };

    std::cout << doc.GetArray().Begin()[0] << '\n';
    */
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
