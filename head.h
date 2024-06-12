#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <deque>
#include <fstream>

class Speaker;

class SpeechManager
{
public:
    SpeechManager();
    ~SpeechManager();
    void show_Meun();
    void exitSystem();
    void initSpeech();
    void creatSpeaker();
    void startSpeech();
    void speechDraw();
    void speechContest();
    void showCore();
    void saveRecord();
    void loadRecord();
    void showRecord();
    void clearRecord();

    bool fileisEmpty;
    std::map<int, std::vector<std::string>> m_Record;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> vVictory;
    std::map<int, Speaker> m_Speaker;
    int m_Index;
};

class Speaker
{
public:
    std::string m_Name;
    double m_Score[2];
};