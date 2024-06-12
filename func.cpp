#include "head.h"

SpeechManager::SpeechManager()
{
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();
}

SpeechManager::~SpeechManager()
{
}

void SpeechManager::show_Meun()
{
    std::cout << "*********************" << std::endl;
    std::cout << "***    1.start    ***" << std::endl;
    std::cout << "***    2.records  ***" << std::endl;
    std::cout << "***    3.clear    ***" << std::endl;
    std::cout << "***    0.exit     ****" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << std::endl;
}

void SpeechManager::exitSystem()
{
    std::cout << "See You" << std::endl;
    system("pause");
    exit(0);
}

void SpeechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();
    this->m_Record.clear();
    this->m_Index = 1;
}

void SpeechManager::creatSpeaker()
{
    std::string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++)
    {
        std::string name = "player_";
        name += nameSeed[i];
        Speaker sp;
        sp.m_Name = name;
        for (int j = 0; j < 2; j++)
        {
            sp.m_Score[j] = 0;
        }
        this->v1.push_back(i + 10001);
        this->m_Speaker.insert(std::make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech()
{
    for (this->m_Index; this->m_Index < 3; this->m_Index++)
    {
        this->speechDraw();
        this->speechContest();
        this->showCore();
    }
    this->saveRecord();

    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();

    std::cout << "比赛结束" << std::endl;
    system("pause");
    system("cls");
}

void SpeechManager::speechDraw()
{
    std::cout << "第" << this->m_Index << " 轮选手" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "result:";
    if (this->m_Index == 1)
    {
        random_shuffle(this->v1.begin(), this->v1.end());
        for (std::vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        random_shuffle(this->v2.begin(), this->v2.end());
        for (std::vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

void SpeechManager::speechContest()
{
    std::cout << "第 " << this->m_Index << " 轮比赛" << std::endl;
    std::multimap<double, int, std::greater<double>> groupScore;
    int num = 0;
    std::vector<int> v_Src;
    if (this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }
    for (std::vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        num++;
        std::deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;
            // std::cout << score << " ";
            d.push_back(score);
        }
        // std::cout << std::endl;
        sort(d.begin(), d.end(), std::greater<double>());
        d.pop_front();
        d.pop_back();
        double sum = accumulate(d.begin(), d.end(), 0.0);
        double avg = sum / (double)d.size();
        // std::cout << *it << " " << this->m_Speaker[*it].m_Name << " " << avg << std::endl;
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
        groupScore.insert(std::make_pair(avg, *it));
        if (num % 6 == 0)
        {
            std::cout << "第 " << num / 6 << " 组名次" << std::endl;
            for (std::multimap<double, int, std::greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                std::cout << (*it).second << ":" << this->m_Speaker[(*it).second].m_Name << " "
                          << this->m_Speaker[(*it).second].m_Score[this->m_Index - 1] << std::endl;
            }
            int count = 0;
            for (std::multimap<double, int, std::greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVictory.push_back((*it).second);
                }
            }
            groupScore.clear();
        }
    }
    std::cout << "第 " << this->m_Index << " 轮结束" << std::endl;
    system("pause");
}

void SpeechManager::showCore()
{
    std::cout << std::endl;
    std::cout << "第" << this->m_Index << " 轮晋级" << std::endl;
    std::vector<int> v;
    if (this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = vVictory;
    }
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " " << this->m_Speaker[*it].m_Name << " "
                  << this->m_Speaker[*it].m_Score[this->m_Index - 1]
                  << std::endl;
    }
    system("pause");
    system("cls");
    this->show_Meun();
}

void SpeechManager::saveRecord()
{
    std::ofstream ofs;
    ofs.open("Speech.csv", std::ios::out | std::ios::app);
    for (std::vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
    {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << std::endl;
    ofs.close();
    std::cout << "Saved!" << std::endl;
    this->fileisEmpty = false;
}

void SpeechManager::loadRecord()
{
    std::ifstream ifs("Speech.csv", std::ios::in);
    if (!ifs.is_open())
    {
        this->fileisEmpty = true;
        std::cout << "文件不存在" << std::endl;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        std::cout << "文件为空" << std::endl;
        this->fileisEmpty = true;
        ifs.close();
        return;
    }
    this->fileisEmpty = false;
    ifs.putback(ch);
    std::string data;
    int index = 0;
    while (ifs >> data)
    {
        std::vector<std::string> v;
        int pos = -1;
        int start = 0;
        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                break;
            }
            std::string temp = data.substr(start, pos - start);
            v.push_back(temp);
            start = pos + 1;
        }
        this->m_Record.insert(std::make_pair(index, v));
        index++;
    }
    ifs.close();
}

void SpeechManager::showRecord()
{
    if(this->fileisEmpty)
    {
        std::cout << "文件不存在或记录为空" << std::endl;
    }
    for (int i = 0; i < this->m_Record.size(); i++)
    {
        std::cout << "第" << i + 1 << "届" << std::endl;
        std::cout << "1." << this->m_Record[i][0] << ":" << this->m_Record[i][1] << " "
                  << "2." << this->m_Record[i][2] << ":" << this->m_Record[i][3] << " "
                  << "3." << this->m_Record[i][4] << ":" << this->m_Record[i][5] << " ";
        std::cout << std::endl;
    }
    system("pause");
    system("cls");
}

void SpeechManager::clearRecord()
{
    std::cout << "是否确认？" << std::endl;
    std::cout << "1.确认" << std::endl;
    std::cout << "2.返回" << std::endl;

    int select = 0;
    std::cin >> select;
    if(select==1)
    {
        std::ofstream ofs("Speech.csv", std::ios::trunc);
        ofs.close();

        this->initSpeech();
        this->creatSpeaker();
        this->loadRecord();
        std::cout << "fine" << std::endl;
    }

    system("pause");
    system("cls");
}