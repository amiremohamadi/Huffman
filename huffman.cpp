#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
using namespace std;

struct Tree_Node
{
	float Value;
	char Alpha;
	Tree_Node *Left;
	Tree_Node *Right;
};

struct DynamicList_Element
{
	DynamicList_Element *Next;
	Tree_Node *Val;
};
struct Dynamic_List
{
	DynamicList_Element *First = new DynamicList_Element;

	void Initialize()
	{
		First->Next = NULL;
	}

	void Add(Tree_Node *Element)
	{
		if (First->Next == NULL)
		{
			DynamicList_Element *DList_New = new DynamicList_Element;
			DList_New->Val = Element;
			DList_New->Next = NULL;
			First->Next = DList_New;
		}
		else
		{
			DynamicList_Element *DList_Element = First;
			bool Add_Last = true;

			while (DList_Element->Next)
			{
				if (DList_Element->Next->Val->Value > Element->Value)
				{
					DynamicList_Element *DList_New = new DynamicList_Element;
					DList_New->Val = Element;
					DList_New->Next = DList_Element->Next;
					DList_Element->Next = DList_New;
					Add_Last = false;
					break;
				}
				DList_Element = DList_Element->Next;
			}
			if (Add_Last == true)
			{
				DynamicList_Element *DList_New = new DynamicList_Element;
				DList_New->Val = Element;
				DList_New->Next = NULL;
				DList_Element->Next = DList_New;
			}
		}
	}

	void Delete_2FirstNode()
	{
		if (First->Next->Next->Next)
		{
			First->Next = First->Next->Next->Next;

			/*delete First->Next->Next->Next;
			delete First->Next->Next;*/
		}
		else
		{
			First->Next = NULL;
		}
	}

	void Print()
	{
		DynamicList_Element *DList_Element = First;
		while (DList_Element->Next)
		{
			cout << DList_Element->Next->Val->Alpha<< " : ";
			cout << DList_Element->Next->Val->Value << "\n";
			DList_Element = DList_Element->Next;
		}
	}
};

void Huffman_Tree_Order(Tree_Node *Root_Node , string Code)
{
	if (Root_Node->Right != NULL || Root_Node->Left != NULL)
	{
		if (Root_Node->Right != NULL)
		{
			string Temp_Code = Code + "1";
			Huffman_Tree_Order(Root_Node->Right , Temp_Code);
		}
		if (Root_Node->Left != NULL)
		{
			string Temp_Code = Code + "0";
			Huffman_Tree_Order(Root_Node->Left , Temp_Code);
		}
	}
	else
	{
		cout << Root_Node->Alpha << ": " << Code << "\n";
	}
}

void Huffman_Code(Dynamic_List *List)
{
	//Initial print
	cout << "\n____________________________________________\n";
	List->Print();

	while (List->First->Next->Next)
	{
		DynamicList_Element *A = List->First->Next;
		DynamicList_Element *B = List->First->Next->Next;

		Tree_Node *A_Node = A->Val;
		Tree_Node *B_Node = B->Val;

		Tree_Node *AB_Node = new Tree_Node;

		if (A_Node->Value < B_Node->Value)
		{
			AB_Node->Left = A_Node;
			AB_Node->Right = B_Node;
		}
		else
		{
			AB_Node->Left = B_Node;
			AB_Node->Right = A_Node;
		}

		//Calculate A+B values
		AB_Node->Value = A_Node->Value + B_Node->Value;
		//For middle nodes label
		AB_Node->Alpha = '+';

		List->Delete_2FirstNode();
		List->Add(AB_Node);
		
		cout << "____________________________________________\n";
		List->Print();
	}
	
	//Finished Huffman
	cout << "\n\nHuffman code of each character:\n\n";
	string Code = "";
	Huffman_Tree_Order(List->First->Next->Val , Code);
}

int main()
{
	string input;
	Dynamic_List *Alphabet_DList = new Dynamic_List;
	Alphabet_DList->Initialize();
	
	cout << "Enter your text that you want to coding with Huffman: ";
	cin >> input ;
	
	for (char s = 'a'; s < 'z';s++)
	{
		float n = count(input.begin(), input.end(), (s));
		if (n != 0)
		{
			Tree_Node *T = new Tree_Node;
			T->Value = n;
			T->Alpha = s;
			T->Left = NULL;
			T->Right = NULL;

			Alphabet_DList->Add(T);
			
			//cout << s << "=" << (n*100) / (input.length()) << "% ";
		}
	}

	Huffman_Code(Alphabet_DList);

	_getch();
	return 0;
}
