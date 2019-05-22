#define _CRT_SECURE_NO_WARNINGS
#include "TTextViewer.h"
#include<string.h>

//#include<string.h>
bool TextEditor::LoadText()
{
	std::ifstream file(PATH);
	char buf[80];
	int len;
	
	while (!file.eof()) {
		file.getline(buf, data->max_sign, '#');
		if (buf[0] == '&') break;
		if (buf[0] == '@')
		{
			len = strlen(buf);
			data->text->data->push_back(*(new TPage));
			data->text->size++;
			data->text->data->Current().data->push_back(*(new TString(len)));
			strcpy(data->text->data->Current().data->Current().str, buf + 1);
			data->text->data->Current().data->Current().size = len - 1;
			data->text->data->Current().size++;
		}
		else
		{
			len = strlen(buf);
			data->text->data->Current().data->push_back(*(new TString(len)));
			strcpy(data->text->data->Current().data->Current().str, buf);
			data->text->data->Current().data->Current().size = len;
			data->text->data->Current().size++;
		}
	}
	data->setCurrent();
	return true;
}


TextEditor::TextEditor(char * path)
{
	PATH = path;
	data = new TEXT;
}

bool TextEditor::PrintAllText()
{
	data->text->data->set_curr_in_first();
	data->text->data->Current().data->set_curr_in_first();
	data->setCurrent();
	std::cout << "\nText name: ";
	fputs(data->name, stdout);
	std::cout << std::endl;
	std::cout << std::endl;
	/*for (size_t i = 0; i < data->text->size; i++)
	{
		std::cout << std::endl;
		std::cout << "Page � " << i + 1<<std::endl;
		std::cout << std::endl;
		for (size_t j = 0; j < data->text->pages->getElem(i).Val.size; j++)
		{
			std::cout << j + 1 << " ";
			fputs(data->text->pages->getElem(i).Val.strings->getElem(j).Val.str, stdout);
			std::cout << std::endl;
		}
	}*/

	std::cout << std::endl;
	std::cout << "Page " << data->cursor.pos_in_text + 1 << std::endl;
	std::cout << std::endl;
	short res = 1;
	do {
		if (res != data->cursor.pos_in_text+1) {
			data->text->data->Current().data->set_curr_in_first();
			res = data->cursor.pos_in_text + 1;
			std::cout << std::endl;
			std::cout << "Page " << res << std::endl;
			std::cout << std::endl;
		}
		std::cout << " ";
		fputs(data->currents->str, stdout);
		std::cout << std::endl;
	} while (data->GoNextString());
	data->setCurrent();
	return true;
}

bool TextEditor::PrintCurPage()
{
	short res = 0;
	std::cout << std::endl;
	std::cout << "Page " << data->cursor.pos_in_text + 1 << std::endl;
	std::cout << std::endl;
	data->currentp->data->set_curr_in_first();
	Goto(data->cursor.pos_in_text, 0, 0);
	while (res++ < data->currentp->size)
	{
		std::cout << " ";
		fputs(data->currents->str, stdout);
		std::cout << std::endl;
		data->GoNextString();
	} 
	data->setCurrent();
	return true;
}

bool TextEditor::PrintCurString()
{
	std::cout << std::endl;
	std::cout << " ";
	fputs(data->currents->str, stdout);
	std::cout << std::endl;
	data->setCurrent();
	return true;
}

bool TextEditor::Copy(char type)
{
	if (type == 'p')
	{
		data->CopyPage();
		return true;
	}
	if (type == 's')
	{
		data->CopyString();
		return true;
	}

	return false;
}

bool TextEditor::Delete(char type)
{
	if (type == 'p')
	{
		data->DeletePage();
		return true;
	}
	if (type == 's')
	{
		data->DeleteString();
		return true;
	}
	return false;

}

bool TextEditor::Cut(char type)
{
	if (type == 'p')
	{
		data->CutPage();
		return true;
	}
	if (type == 's')
	{
		data->CutString();
		return true;
	}
	return false;
}

bool TextEditor::Insert()
{
	data->insert();
	return false;
}

bool TextEditor::Change(char type)
{
	if (type == 'p')
	{
		data->ChangePage();
		return true;
	}
	if (type == 's')
	{
		data->ChangeString();
		return true;
	}
	return false;
}

bool TextEditor::Goto(short p, short S, short s)
{
	data->GoToPos({ p,S,s });
	return false;
}

bool TextEditor::InsertBack()
{
	data->text->data->push_back(*data->Buffer);
	data->text->size++;

	return false;
}

bool TextEditor::SaveText()
{
	std::ofstream file("output.txt");
	char buf[80];
	bool flag = true;
	short res=0;
	file << '@';
	while (flag) {
		if (res != data->cursor.pos_in_text)
		{
			res = data->cursor.pos_in_text;
			file << '@';
		}
		file << data->currents->str << '#';
		flag = data->GoNextString();
	}
	file << '&';
	data->setCurrent();
	return true;

}

bool TextEditor::SaveText(char * path)
{
	return false;
}
