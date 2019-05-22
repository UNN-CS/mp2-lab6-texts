#include "TText.h"

TEXT::TEXT()
{
	text = new Text;
}

void TEXT::setCurrent()
{
	currentp = &text->data->set_cur(0).Val;
	currents = &text->data->set_cur(0).Val.data->set_cur(0).Val;
	cursor = { 0,0,0 };
}

bool TEXT::GoNextString()
{
	if (cursor.pos_in_page < currentp->size-1)
	{
		currents = &(currentp->data->GoNext());
		cursor.pos_in_page++;
		cursor.pos_in_string = 0;
		return true;
	}
	else
	{
		currentp->data->set_curr_in_first();
		return GoNextPage();
	}
}

bool TEXT::GoNextPage()
{
	if (cursor.pos_in_text < text->size-1)
	{
		currentp = &(text->data->GoNext());
		currentp->data->set_curr_in_first();
		currents = &(currentp->data->Current());
		cursor.pos_in_text++;
		cursor.pos_in_page = 0;
		cursor.pos_in_string = 0;
		return true;
	}
	else return false;
}

bool TEXT::GoBackString()
{
	if (cursor.pos_in_page > 0)
	{
		currents = &(currentp->data->GoBack());
		cursor.pos_in_page--;
		cursor.pos_in_string = currents->size;
		return true;
	}
	else return GoBackPage();
}

bool TEXT::GoBackPage()
{
	if (cursor.pos_in_text > 0)
	{
		currentp = &(text->data->GoBack());
		cursor.pos_in_text--;
		cursor.pos_in_page = currentp->size;
		cursor.pos_in_string = currents->size;
		return true;
	}
	else return false;
}

bool TEXT::GoToPos(Position pos)
{
	if (pos.pos_in_text >= 0 && pos.pos_in_text < text->size)
		if (pos.pos_in_page >= 0 && pos.pos_in_page < text->data->getElem(pos.pos_in_text).Val.size)
			if (pos.pos_in_text >= 0 && pos.pos_in_string < text->data->getElem(pos.pos_in_text).Val.data->getElem(pos.pos_in_page).Val.size)
			{
				cursor = pos;
				currents = &(text->data->set_cur(pos.pos_in_text).Val.data->set_cur(pos.pos_in_page).Val);
				currentp = &(text->data->set_cur(pos.pos_in_text).Val);
				return true;
			}
	return false;
}

bool TEXT::DeleteString()
{
	text->data->getElem(cursor.pos_in_text).Val.data->popc(cursor.pos_in_page);
	text->data->getElem(cursor.pos_in_text).Val.size--;
	CorrectCursor();
	currents = &text->data->set_cur(cursor.pos_in_text).Val.data->set_cur(cursor.pos_in_page).Val;
	return false;
}

bool TEXT::DeletePage()
{
	text->data->popc(cursor.pos_in_text);
	text->size--;
	CorrectCursor();
	currentp = &text->data->set_cur(cursor.pos_in_text).Val;
	return false;
}

bool TEXT::CutString()
{
	Buffer = currents;
	DeleteString();
	
	return false;
}

bool TEXT::CutPage()
{
	Buffer = currentp;
	DeletePage();
	
	return false;
}

bool TEXT::ChangeString()
{
	currents->str = Buffer->str;
	return false;
}

bool TEXT::ChangePage()
{
	text->data->pop(cursor.pos_in_text);
	text->data->insert(*Buffer, cursor.pos_in_text);
	currentp = &text->data->set_cur(cursor.pos_in_text).Val;
	return false;
}

bool TEXT::CopyString()
{
	Buffer = currents;
	CorrectCursor();
	return false;
}

bool TEXT::CopyPage()
{
	Buffer = currentp;
	CorrectCursor();
	return false;
}

bool TEXT::insert()
{
	if (Buffer->type == 'p')
	{
		text->data->insert(*Buffer, cursor.pos_in_text);
		text->size++;
		currentp = &text->data->set_cur(cursor.pos_in_text).Val;
		currents = &text->data->set_cur(cursor.pos_in_text).Val.data->getElem(0).Val;
		return true;
	}
	if (Buffer->type == 's')
	{
		currentp->data->insert(*Buffer, cursor.pos_in_page);
		currentp->size++;
		currents = &text->data->set_cur(cursor.pos_in_text).Val.data->set_cur(cursor.pos_in_page).Val;
		return true;
	}
	return false;
}

bool TEXT::insertStr(char * str)
{
	return false;
}

void TEXT::CorrectCursor()
{
	if (cursor.pos_in_text >= text->size) cursor.pos_in_text = text->size - 1;
	if (cursor.pos_in_page >= text->data->getElem(cursor.pos_in_page).Val.size) cursor.pos_in_page = text->data->getElem(cursor.pos_in_page).Val.size - 1;
}
