#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

struct Files{
    string name;
    string filename;
};

struct Questions{
    string questions;
    string choices[6];
    string answer;
    int flags;
};

string ExePath(){
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}

int main()
{
    Files file[100];
    int total_file = 0;
    string input_files = ExePath() + "\\files.txt";
    ifstream in_stream;
    //ofstream out_stream;
    in_stream.open(input_files.c_str());
    if(in_stream.fail()){
        cout << "Check the file director path!";
    }else{
        char next[1000];
        int counter = 0;
        int choice = 0;

        //in_stream >> next;
        while(!in_stream.eof()){
            //in_stream >> next;
            Files f1;
            in_stream >> f1.name;
            in_stream >> f1.filename;
            file[counter] = f1;
            counter++;
        }
        while(true){
            total_file = counter;
            system("CLS");
            cout << "\nSelect Question Type:";
            for(int i=0;i<total_file;i++){
                cout << "\n\t" << (i+1) << " - " << file[i].name << " - Filename: " << file[i].filename;
            }
            cout << "\n\t" << "Press: " << (total_file+1) << " to EXIT" << endl;
            cout << "\nCHOICE: ";
            cin >> choice;
            if(choice <= total_file){
                Questions q[500];
                int total_questions = 0;
                Files selected_file = file[choice-1];
                ifstream q_stream;
                string sel_file = ExePath() + "\\" + selected_file.filename;
                q_stream.open(sel_file.c_str());
                if(q_stream.fail()){
                    cout << "Check the question filename test bank!";
                }else{
                    Questions q1;
                    int c1 = 0;
                    string trash;
                    while(!q_stream.eof()){
                        getline(q_stream,q1.questions,'?');
                        getline(q_stream,trash);

                        for(int j=0;j<6;j++){
                            string temp_answer = "";
                            getline(q_stream,temp_answer);
                            //cout << temp_answer << endl;
                            switch(temp_answer[0]){
                                case 'a':
                                case 'A':
                                case 'b':
                                case 'B':
                                case 'c':
                                case 'C':
                                case 'd':
                                case 'D':
                                case 'E':
                                case 'e':
                                case 'F':
                                case 'f':
                                case 'G':
                                case 'g':
                                         //cout << "CHOICES " << temp_answer << endl;
                                         if(temp_answer.length()>2 && temp_answer[1]=='.'){
                                            q1.choices[j] = temp_answer;
                                         }else{
                                            for(int m = j; m < 6; m++){
                                                q1.choices[m] = " ";
                                            }
                                            q1.answer = temp_answer;
                                            j = 7;
                                         }
                                         break;
                                default:
                                        q1.answer = temp_answer;
                                        j = 7;
                            }
                        }
                        q1.flags = 0;
                        q[c1] = q1;
                        c1++;
                    }
                    total_questions = c1;
                }
                q_stream.close();
                string c_continue = "y";
                string answer = "ANSWER";
                int randCounter = 1;
                int prevX = -1;
                int members = total_questions<10?1:10;
                int group = total_questions%members==0?(total_questions/members):(total_questions/members)+1;
                int groupStart = rand()%group;
                int x = 0;
                do{
                    if(randCounter>=(members/2)){
                        randCounter = 1;
                        groupStart = rand()%group;
                    }else{
                        x = (groupStart*members) + (rand()%(members));
                    }
                    randCounter++;

                    system("CLS");
                    x = (x>=total_questions)||(x<0)?rand()%(total_questions-1):x;

                    if(prevX==x){
                        x = x==0||(x+1)==total_questions?0:x+1;
                    }
                    prevX = x;
                    cout << "QUESTION: \n\t";
                    cout << q[x].questions << endl;
                    for(int i=0;i<6;i++){
                        cout << "\n\t" << q[x].choices[i];
                    }
                    cout << "\nGUESS: ";
                    cin.get();
                    getline(cin , answer, '\n');
                    cout << "\n\n\tCORRECT - " << q[x].answer;
                    cout << "\n\tContinue? Press (Y/y) : ";
                    cin >> c_continue;
                }while(c_continue=="Y"||c_continue=="y");

            }else{
                return 0;
            }
        }
    }
    in_stream.close();
    return 0;
}
