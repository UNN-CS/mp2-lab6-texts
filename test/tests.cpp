#include <gtest.h>
#include <iostream>
#include <sstream>
#include "ttext.h"
#include "ttextlink.h"

TEST(TText, can_init_and_clean_memory) {
    ASSERT_NO_THROW(
        TTextLink::InitMemSystem();
        TText txt;
        TTextLink::MemCleaner(txt);
    );
}

TEST(TText, can_insert_and_go_to_next_line) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("abacaba");
    ASSERT_NO_THROW(txt.GoNextLink());
    ASSERT_EQ("abacaba", txt.GetLine());
}

TEST(TText, can_insert_and_go_to_down_line) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("abacaba");
    ASSERT_NO_THROW(txt.GoDownLink());
    ASSERT_EQ("abacaba", txt.GetLine());
}

TEST(TText, can_delete_next_line) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("abacaba");
    ASSERT_NO_THROW(txt.DelNextLine());
    ASSERT_ANY_THROW(txt.GoNextLink());
}

TEST(TText, can_delete_down_line) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("abacaba");
    ASSERT_NO_THROW(txt.DelDownLine());
    ASSERT_ANY_THROW(txt.GoDownLink());
}

TEST(TText, can_insert_and_go_to_next_section) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextSection("abacaba");
    ASSERT_NO_THROW(txt.GoNextLink());
    ASSERT_EQ("abacaba", txt.GetLine());
}

TEST(TText, can_insert_and_go_to_down_section) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownSection("abacaba");
    ASSERT_NO_THROW(txt.GoDownLink());
    ASSERT_EQ("abacaba", txt.GetLine());
}

TEST(TText, can_delete_next_section) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextSection("abacaba");
    ASSERT_NO_THROW(txt.DelNextSection());
    ASSERT_ANY_THROW(txt.GoNextLink());
}

TEST(TText, can_delete_down_section) {
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownSection("abacaba");
    ASSERT_NO_THROW(txt.DelDownSection());
    ASSERT_ANY_THROW(txt.GoDownLink());
}

TEST(TText, can_copy_text_with_only_downlines) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsDownLine("aba");
    txt.InsDownLine("caba");
    txt.InsDownLine("def");
    txt.InsDownLine("lul2");
    txt.InsDownLine("lul4");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}

TEST(TText, can_copy_text_with_only_nextlines) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsNextLine("aba");
    txt.InsNextLine("caba");
    txt.InsNextLine("def");
    txt.InsNextLine("lul2");
    txt.InsNextLine("lul4");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}

TEST(TText, can_copy_text_with_only_downsectios) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsDownSection("aba");
    txt.InsDownSection("caba");
    txt.InsDownSection("def");
    txt.InsDownSection("lul2");
    txt.InsDownSection("lul4");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}

TEST(TText, can_copy_text_with_only_nextsection) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsNextSection("aba");
    txt.InsNextSection("caba");
    txt.InsNextSection("def");
    txt.InsNextSection("lul2");
    txt.InsNextSection("lul4");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}

TEST(TText, can_copy) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsNextSection("ada");
    txt.InsNextSection("cab");
    txt.InsDownSection("aba");
    txt.InsDownLine("caba");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}

TEST(TText, can_copy_2) {
    TTextLink::InitMemSystem();
    TText txt;
    std::stringstream t1, t2;
    txt.InsNextLine("ada");
    txt.InsNextSection("cab");
    txt.InsDownSection("aba");
    txt.InsDownLine("caba");
    txt.InsDownSection("ba");
    txt.Print(t1);
    PTText txt2 = txt.GetCopy();
    txt2->Print(t2);
    ASSERT_NE(&txt, txt2);
    ASSERT_EQ(t2.str(), t1.str());
}
