#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define A 7
#define NO -1
#define START 8

using namespace std;

template<class T> struct MyHash;

template<> struct MyHash<string>
{
    size_t operator()(const string str, int m)
    {
        size_t hash = 0;
        for( int i = 0; i < str.size(); i++)
        {
            hash = (hash * A + str[i]);
        }
        return hash % m;
    }
};

template<class T> struct MyHash2;

template<> struct MyHash2<string>
{
    size_t operator()(const string str, int m)
    {
        size_t hash = 0;
        for( int i = 0; i < str.size(); i++)
        {
            hash = (hash * A + str[i]);
        }

        if (hash % 2 == 0)
        {
          hash++;
        }
        return hash % m;
    }
};


template<class Hash = MyHash<string>,class Hash2 = MyHash2<string> >
class HashTable {
public:

    HashTable(int size, Hash hashfunc = MyHash<string>()):
    max_size(size), real_size(0) {
        for( int i = 0; i < max_size; ++i)
            table.push_back(empty);
    };

    HashTable& operator = (HashTable& Ref)
    {
      if (this == &Ref)
        {
          return *this;
        }

      table = Ref.table;
      max_size = Ref.max_size;
      return *this;

    };

    bool add(string str)  {
      if( find( str ) != NO)
  			return false;

      int h = hash(str, max_size);
      int h2 = hash2(str, max_size);

      int j = h;
      int step = 0;
  		while( table[j] != empty && table[j] != deleted ) {
  			j = next(h, h2, ++step);
  		}
  		table[j] = str;
      real_size++;

  		if( real_size*4 == max_size*3 ) {
  			grow();
  		}
  		return true;
    };

    bool remove(string str){
        int state = find(str);

        //нет в таблице
        if(state == NO)
            return false;

        //есть в таблице
        table[state] = deleted;
        --real_size;
        return true;

    };

    int find(string str){

      int h = (int)hash(str, max_size);
      int h2 = (int)hash2(str, max_size);

      int j = h;
      int step = 0;

      if (table[h] == str)
        return h;
      if (table[h] == empty)
        return NO;

		  j = next(h, h2, ++step);

  		while( table[j] != empty ) {

    			if( table[j] == str) {
    				return j;
    			}
    			if( j == h ){
    				return NO;
          }
    			j = next(h, h2, ++step);
    		}
      return NO;
    };

private:
    Hash hash;
    Hash2 hash2;
    vector<string> table;
    int max_size;
    int real_size;

    string deleted = "DELETE";
    string empty = "EMPTY";

    //функция получает уже хеш строки, чтобы не пересчитывать его
    int next(int hash, int hash2, int i)  {
        return (hash + i*hash2) % max_size;
    };

    void grow()  {
        HashTable<> new_table(max_size*2);

        for (size_t i = 0; i < max_size; i++) {

          if (table[i] != empty && table[i] != deleted)
          {
            new_table.add(table[i]);
          }
        }

        *this = new_table;
    };
};



int main(void) {

    HashTable<> mytable(START);
    string state;

    while( getline(cin, state)) {
        if (state.empty())
            continue;

        char command_type;
        string data;
        istringstream stream(state);
        stream >> command_type >> data;

        if( command_type == '+' ) {
            if( mytable.add(data))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
        else if( command_type == '?' ) {
            if( mytable.find(data) != NO  )
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
        else if( command_type == '-' ) {
            if( mytable.remove(data))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
    }
    return 0;
}
