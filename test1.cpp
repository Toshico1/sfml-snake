#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

enum {up = 0, down, left, right};

int current_global_way = down;

class Snake
{
private:
    /* data */
public:
    int p_y = 100;
    int p_x = 100;
    RenderWindow *window;
    RectangleShape block_snake[1000]; //массив блоков змей
    int len_of_snake = 7;
    int start_block = 6;
    int current_head = 0;
    int way = down; // 0-up | 1-down | 2-left | 3-right

    Snake(RenderWindow *window);
    ~Snake();
    void render();
    void move();
    void setWay(int x);
};

void Snake::render(){
    for(int i=0; i < len_of_snake; i++){
        this->window->draw(block_snake[i]);
    }


}


Snake::Snake(RenderWindow *window)
{
    this->window = window;
    for(int i=1; i < len_of_snake;i++){
        block_snake[i] = RectangleShape(Vector2f(8, 8));
        block_snake[i].setFillColor(Color::Blue);
        block_snake[i].setPosition(250, 250-(i*10));
        std::cout << i << "=i " << block_snake[i].getPosition().y << "=y\n";
    }
    block_snake[current_head] = RectangleShape(Vector2f(10, 10));
    block_snake[current_head].setFillColor(Color::Magenta);
    block_snake[current_head].setPosition(250, 250);
    render();
    
}

void Snake::setWay(int way_){
    this->way = way_;
}

void Snake::move(){
    
    int x = block_snake[current_head].getPosition().x;
    int y = block_snake[current_head].getPosition().y;

    std::cout << start_block << "=s_b, " << current_head << "=c_h " << x << "=x " << std::endl;  

    //std::cout << x << "=x, y=" << y << std::endl;
    if (way == down){
        block_snake[start_block].setPosition(x, y+10);
        //std::cout << "================================\n";
        //std::cout << x << "=x, y=" << y << std::endl;
        //std::cout << "================================\n";     

    }
    if (way == up){
        block_snake[start_block].setPosition(x, y-10);


    }
    if (way == left){
        block_snake[start_block].setPosition(x-10, y);
 

    }
    if (way == right){
        block_snake[start_block].setPosition(x+10, y);

    }

    current_head = start_block;
    if (start_block-1 < 0){
        start_block = len_of_snake-1;
    }
    else{
        start_block--;
    }       
    
    
    
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
};

Food::Food(RenderWindow *win)
{
    p_x = rand() % 600+5;
    p_y = rand() % 600+4;
    eat = new RectangleShape(Vector2f(10, 10));
    eat->setFillColor(Color::Green);
    eat->setPosition(p_x, p_y);
    win->draw(*eat);
}


 
int main()
{
    int i = 0;
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(600, 600), "Snake");
    // Экземпляр еды
    Food f1 = Food(&window); //создаем экземпляр еды
    Snake snake = Snake(&window);
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
                    if ((current_global_way != down) && (current_global_way != up)){
                        snake.setWay(up);
                        current_global_way = up;
                    }
                }

                if (event.key.code == sf::Keyboard::Down){
                    std::cout << "Down" << std::endl;
                    if ((current_global_way != down) && (current_global_way != up)){
                        snake.setWay(down);
                        current_global_way = down;
                    }    
                }

                if (event.key.code == sf::Keyboard::Left){
                    std::cout << "Left" << std::endl;
                    if((current_global_way != left) && (current_global_way != right)){
                        snake.setWay(left);
                        current_global_way = left;
                    }
                }
                if (event.key.code == sf::Keyboard::Right){
                    std::cout << "Right" << std::endl;
                    if((current_global_way != left) && (current_global_way != right)){
                        snake.setWay(right);
                        current_global_way = right;
                    }
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
            sf::Time time_sleep = sf::seconds(1.0);
            sf::sleep(time_sleep);
            snake.move();
            
            snake.render();
        //и в конце выводим все на экран:
        window.display();
	}
 
	return 0;
}
