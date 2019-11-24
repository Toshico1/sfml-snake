#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

 
int main()
{

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(600, 600), "SFML Works!");
	
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// Тогда закрываем его
				window.close();
		}
	// Отрисовка окна
        RectangleShape lines[100][2];	//[][0] - vert [][1] - hor
        
        //рисуем поле
        for(int i=0; i < 100; i++){
            RectangleShape line_v(Vector2f(600, 2)); 
            RectangleShape line_h(Vector2f(600, 2));
            line_v.setPosition(i*10, 0);
            line_h.setPosition(0, i*10);
            line_v.rotate(90);
            //line_h.rotate(90); не нужно
            line_v.setFillColor(Color(i+100, i, i+20));
            line_h.setFillColor(Color(i+100, i, i+20));
            lines[i][0] = line_v;
            lines[i][1] = line_h;
        }
        //далее для каждой из точек задаем свою позицию:

        for(int i=0; i < 100; i++){
            window.draw(lines[i][0]);
        }
        for(int i=0; i<100; i++){
            window.draw(lines[i][1]);
        }
        //и в конце выводим все на экран:
        window.display();
	}
 
	return 0;
}