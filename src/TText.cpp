#include "TText.h"
#include "TTextLink.h"
#include <fstream>
#define BufLength 80

static char StrBuf[BufLength+1]; // буфер для ввода строк
static int TextLevel;            // номер текущего уровня текста

TText::TText(PTTextLink pl) {
    if(pl == nullptr)
        pl = new TTextLink();
    pFirst = pl;
	pCurrent = pFirst;
}

//навигация
void TText::GoFirstLink() { // переход к первой строке
    while(!Path.empty())
        Path.pop(); // очистка стека
    pCurrent = pFirst;
    if(pCurrent == nullptr)
        throw TextError;
}

void TText::GoDownLink() { // переход к след. строке по Down
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent -> pDown == nullptr)
        throw TextError;
    Path.push(pCurrent);
    pCurrent = pCurrent->pDown;
}

void TText::GoNextLink() { // переход к следующей строке по Next
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent -> pNext == nullptr)
        throw TextError;
    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
}

void TText::GoPrevLink() { // переход к пред. позиции в тексте
    if(Path.empty())
        throw TextNoPrev;
    pCurrent = Path.top();
    Path.pop();
}

//доступ
std::string TText::GetLine() { // чтение теущей строки
    if(pCurrent == nullptr)
        return std::string("");
    else
        return std::string(pCurrent->Str);
}
void TText::SetLine(std::string s) { // замена текущей строки
    if(pCurrent == nullptr)
        throw TextError;
    strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = '\0';
}

//модификация
void TText::InsDownLine(std::string s) { // вставка строки в подуровень
    if(pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", pd, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength-1] = '\0';
    pCurrent->pDown = pl;
}

void TText::InsDownSection(std::string s) { // вставка раздела в подуровень
    if(pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", nullptr, pd);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength-1] = '\0';
    pCurrent->pDown = pl;
}

void TText::InsNextLine(std::string s) { // вставка строки в том же уровне
    if(pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", pd, nullptr); // ?????
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength-1] = '\0';
    pCurrent->pNext = pl;
    // >:-/
}

void TText::InsNextSection(std::string s) { // вставка раздела в том же уровне
    if(pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", nullptr, pd);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength-1] = '\0';
    pCurrent->pNext = pl;
    // >:-/
}


void TText::DelDownLine() { // удаление строки в подуровне
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent->pDown != nullptr) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if(pl1->pDown == nullptr)
            pCurrent->pDown = pl2;
    }
}

void TText::DelDownSection() { // удаление раздела в подуровне
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent->pDown != nullptr) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}

void TText::DelNextLine() { // удаление строки в том же уровне
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if(pl1->pNext == nullptr)
            pCurrent->pNext = pl2;
    }
    // >:-/
}

void TText::DelNextSection() { // удаление раздела в том же уровне
    if(pCurrent == nullptr)
        throw TextError;
    if(pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
    // >:-/
}

// итератор
int TText::Reset() { // установить на первую запись
    while(!St.empty())
        St.pop();
    // Текущая строка в стеке не хранится
    // исключение - первая строка текста, которая на дне стека
    pCurrent = pFirst;
    if(pCurrent != nullptr) {
        St.push(pCurrent);
        if(pCurrent->pNext != nullptr)
            St.push(pCurrent->pNext);
        if(pCurrent->pDown != nullptr)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded() const { // таблица завершена?
    return !St.size();
}

int TText::GoNext() { // переход к следующей записи
    if(!IsTextEnded()) {
        pCurrent = St.top();
        St.pop();                   // если после выборки стек пуст, значит
        if(pCurrent != pFirst) {    // первая строка текста уже была обработана
            if(pCurrent->pNext != nullptr)
                St.push(pCurrent->pNext);
            if(pCurrent->pDown != nullptr)
                St.push(pCurrent->pDown);
        }
    }
    return IsTextEnded();
}

// копирование текста
PTTextLink TText::GetFirstAtom(PTTextLink pl) { // поиск первого атома
    PTTextLink tmp = pl;
    while(!tmp->IsAtom()) {
        St.push(tmp);
        tmp = tmp->GetDown();
    }
    return tmp;
}

PTText TText::GetCopy() { // копирование текста
    PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;
    if(pFirst != nullptr) {
        while(!St.empty())
            St.pop();
        while(true) {
            if(pl != nullptr) { //  переход к первому атому
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->GetDown();
            }
            else if(St.empty())
                break;
            else {
                pl1 = St.top();
                St.pop();
                if(strstr(pl1->Str, "Copy") == nullptr) { // первый этап создания копии
                    // создание копии - pDown на уже скопированный подуровень
                    pl2 = new TTextLink("Copy", pl1, cpl); // pNext на оригинал
                    St.push(pl2);
                    pl = pl1->pNext;
                    cpl = nullptr;
                    // >:-/
                }
                else { // второй этап создания копии
                        pl2 = pl1->GetNext();
                        strcpy(pl1->Str, pl2->Str);
                        pl1->pNext = cpl;
                        cpl = pl1;
                    // >:-/
                }
            }
        }
    }
    return new TText(cpl);
}

// печать текста
void TText::Print() {
    TextLevel = 0;
    PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl) {
    if(ptl != nullptr) {
        for(int i = 0; i < TextLevel; i++)
            std::cout<<" ";
        std::cout<<" ";
        ptl->Print(std::cout);
        std::cout<<std::endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}

// чтение текста из файла
void TText::Read(const char * pFileName) {
    std::ifstream TxtFile(pFileName);
    TextLevel = 0;
    if(!TxtFile.is_open())
        throw TextError;
    pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(std::ifstream& TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while(TxtFile.eof() == 0) {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if(StrBuf[0] == '}') {
            TextLevel--;
            break;
        }
        else if(StrBuf[0] == '{') { // рекурсия
            ptl->pNext = new TTextLink(StrBuf, nullptr, nullptr);
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if(pHead->pDown == nullptr) { // удаление первой строки, если нет подуровня
        pHead = pHead->pNext;
        delete ptl;
    }
    return pHead;
}
