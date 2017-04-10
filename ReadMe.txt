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
 
 замыкание
 
callback
