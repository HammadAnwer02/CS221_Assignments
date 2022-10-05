#include<iostream>
using namespace std;
class Phone_directory {
	struct node {
		string key;
		string name;
		string address;
		string email;
		node* next;
		node* top;
		node* bottom;
		node* previous;
		node()
		{
			next = nullptr;
			top = nullptr;
			bottom = nullptr;
			previous = nullptr;
		}
	};
	node* head;
	int max_rows;
	int max_cols;
	int final_node_row;
	int final_node_col;

public:
	Phone_directory(int r = 3, int c = 5)
	{
		head = nullptr;
		max_rows = r;
		max_cols = c;
		final_node_row = 1;
		final_node_col = 1;
	}
	void set_data(node* newnode)
	{
		cout << "Enter the Phone_Number.\n";
		cin >> newnode->key;
		cout << "Enter the name of the Contact.\n";
		cin >> newnode->name;
		cout << "Enter the address of the contact.\n";
		cin >> newnode->address;
		cout << "Enter the email of the Contact(if any, else write N/A).\n";
		cin >> newnode->email;
	}
	node* finding_last_node()
	{
		int row_count = 1;
		int col_count = 1;
		node* temp = head;
		if (temp == nullptr)
			return temp;
		else {
			while (true)
			{
				if (col_count == max_cols && row_count != max_rows)
				{
					node* temp2 = temp;
					while (temp2->previous != nullptr)
					{
						temp2 = temp2->previous;
					}
					if (temp2->bottom != nullptr)
					{
						temp = temp2;
						col_count = 1;
						temp = temp->bottom;
						row_count++;
					}
					else
						break;
				}
				else if (temp->bottom != nullptr || temp->next != nullptr)
				{
					temp = temp->next;
					col_count++;
				}
				else
					break;

			}

			return temp;
		}
	}
	node* finding_top_node(int row_count, int col_count)
	{
		node* temp = head;

		for (int i = 0; i < row_count - 1; i++)
		{
			temp = temp->bottom;
		}
		for (int i = 0; i < col_count; i++)
		{
			temp = temp->next;
		}
		return temp;
	}
	int get_final_node_col()
	{
		return final_node_col;
	}
	int get_final_node_row()
	{
		return final_node_row;
	}
	void Insert_number()
	{
		if (final_node_col == max_cols && final_node_row == max_rows)
		{
			cout << "The Directory is already full!.\n";
		}
		else
		{
			node* newnode = new node;
				set_data(newnode);
			if (head == nullptr)
			{
				newnode->next = nullptr;
				head = newnode;
			}
			else
			{
				node* temp;
				node* temp_top = head;
				temp = finding_last_node();
				if (final_node_col == max_cols)
				{
					while (temp->previous != nullptr)
					{
						temp = temp->previous;
					}
					temp->bottom = newnode;
					newnode->top = temp;
				}
				else
				{
					if (temp->top != nullptr)
					{
						temp->next = newnode;
						newnode->previous = temp;
						newnode->next = nullptr;
						temp_top = finding_top_node(final_node_row, final_node_col);
						temp_top->bottom = newnode;
						newnode->top = temp_top;
						newnode->bottom = nullptr;
					}
					else
					{
						temp->next = newnode;
						newnode->previous = temp;
						newnode->next = nullptr;
					}
				}
			}
			if (final_node_col == max_cols)
			{
				final_node_col = 1;
				final_node_row++;
			}
			else
				final_node_col++;
		}


	}
	void Display()
	{
		int row_count = 1;
		int col_count = 1;
		node* temp = head;
		while (1)
		{
			if (head == nullptr)
			{
				cout << "The List is empty.\n";
				break;
			}

			else if (col_count == max_cols && row_count != max_rows)
			{
				node* temp2 = temp;
				while (temp2->previous != nullptr)
				{
					temp2 = temp2->previous;
				}
				if (temp2->bottom != nullptr)
				{
					temp = temp2;
					col_count = 1;
					temp = temp->bottom;
					row_count++;
				}
				else
					break;
			}
			else if (temp->bottom != nullptr || temp->next != nullptr)
			{
				cout << endl << temp->key << endl;
				temp = temp->next;
				col_count++;
			}
			else
				break;
		}
	}

};