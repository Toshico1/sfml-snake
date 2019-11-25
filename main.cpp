#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Snake
{
private:
    /* data */
public:
    int p_y = 100;
    int p_x = 100;
    RenderWindow *window;
    Snake(RenderWindow *window);
    ~Snake();
    void render();
};

Snake::Snake(RenderWindow *window)
{
    this->window = window;
    RectangleShape snake_block(Vector2f(4, 4));
}

Snake::~Snake()
{
}


class Food
{
private:
    /* data */
public:
    int p_x = 0;
    int p_y = 0;
    RectangleShape *eat;
    RenderWindow *win;

    Food(RenderWindow *win);
    RectangleShape &getFood();
    ~Food();
};

Food::Food(RenderWindow *win)
{
    p_x = rand() % 600+1;
    p_y = rand() % 600+1;
    eat = new RectangleShape(Vector2f(4, 4));
    eat->setFillColor(Color::Green);
    eat->setPosition(p_x, p_y);
    win->draw(*eat);
}
RectangleShape &Food::getFood(){
    //return *eat; //WTF &?
}

Food::~Food()
{
    
}

 
int main()
{

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(600, 600), "Snake");
	
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
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Up)
                    std::cout << "Up" << std::endl;
                if (event.key.code == sf::Keyboard::Down)
                    std::cout << "Down" << std::endl;
                if (event.key.code == sf::Keyboard::Left)
                    std::cout << "Left" << std::endl;
                if (event.key.code == sf::Keyboard::Right)
                    std::cout << "Right" << std::endl;
            }
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
        Food f1 = Food(&window); //создаем экземпляр еды

        //и в конце выводим все на экран:
        window.display();
	}
 
	return 0;
}