#include "head.h"

int main()
{
    srand((unsigned)time(NULL));
    SpeechManager sm;
    // for (std::map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end();it++)
    // {
    //     std::cout << (*it).first << " " << (*it).second.m_Name << std::endl;
    // }
    int choice = 0;
    while(true)
    {
        sm.show_Meun();
        std::cout << "choose: ";
        std::cin >> choice;
        std::cout << std::endl;
        switch(choice)
        {
        case 1:
            sm.startSpeech();
            break;
        case 2:
            sm.showRecord();
            break;
        case 3:
            sm.clearRecord();
            break;
        case 0:
            sm.exitSystem();
            break;
        default:
            system("cls");
            break; 
        }
    }

    system("pause");
    return 0;
}