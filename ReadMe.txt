указатель на функцию
int f(int a,float b )
return (int(b))+a
}
int (*f)(int,float)=&f;
cout<<f(5,7.2)

функция возвращает ссылку на др функцию
function <int(int,float)> gen f(){return &f}
 
 лямбда функция(безымянная)
 int func(int i){return i}
 int a;
 f(int agr1,func(int i)) --> f(int agr1,[a](int(i))->int{return i+a}) //чтобы использовалась именно а вне реализации лямбда функции
 
 замыкание closure
 
callback

функция высшего порядка - которая принимает в качестве аргумента или возвращает другую функцию 
map
reduce
filter

typedef

winapi - оконные приложения в С++
https://msdn.microsoft.com/ru-ru/library/bb384843
https://habrahabr.ru/post/164193/
библиотеки windows.h
           stdio.h
           string

throw exeptiom

тернарный оператор
