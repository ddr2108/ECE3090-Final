#ifndef LIST_H
#define LIST_H

//NOTE THAT THIS IS "STARTER CODE". IT IS <<NOT>> A FULLY COMPLETE CLASS.
//NOTICE, FOR EXAMPLE, THAT THE COPY CONSTRUCTOR HAS NOT BEEN IMPLEMENTED.

template <class T> class list {

  protected:

    int arraysize; //Maximum allowed size of list

    T *array;      //Array used to hold list items
    T *current;    //Pointer to next list item to be read (sequential access)
    T *tail;       //Pointer to first empty item in list

  public:

    //Contructors

    list() {array=current=tail=0; arraysize=0;}

    list(int maxsize) {array=0; allocate(maxsize);}

    ~list() {deallocate();}

    //Memory allocation

    int allocate(int maxsize) {
      if (arraysize!=maxsize) {
        deallocate();
	if (!(array=new T[maxsize])) return 0;
      }
      arraysize=maxsize;
      clear();
      return 1;
    }

    void deallocate() {
      delete[] array;
      array=current=tail=0;
      arraysize=0;
    }

    //Manipulating the list

    void clear() {current=tail=array;}

    void append(T item) {*tail++=item;} //Does not check for overstepping array

    int getSize() {return tail-array;}

    //Sequential access

    void rewind() {current=array;}

    int getNext(T &item)
     {if (current!=tail) {item=*current++; return 1;} else return 0;}

    void deleteNext()
     {if (current!=tail) *current=*--tail;}

    void fforward() {current=tail;}

    int getPrev(T &item)
     {if (current!=array) {item=*--current; return 1;} else return 0;}

};

#endif
