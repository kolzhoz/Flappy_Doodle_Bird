#include <SFML/Graphics.hpp>-
#include <iostream>

using namespace std;
using namespace sf;
RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
class Hero {
	Texture heroT;
	float xSpeed, ySpeed;
public:
	Sprite hero;
	Vector2f lastPos, currentPos;
	Hero() {
		hero.setPosition(-100, 905);
		lastPos = { -100,905 };
		currentPos = { -100, 905 };
		hero.setScale(0.2, 0.2);
		xSpeed = 0; ySpeed = 0;
		heroT.loadFromFile("140657.png");
		hero.setTexture(heroT);
	}
	Vector2f getPosition() {
		return hero.getPosition();
	}
	bool setPosition(float x, float y) {
		hero.setPosition(x, y);
		return 1;
	}
	bool setXSpeed(float speed) {
		xSpeed = speed;
		return 1;
	}
	bool setYSpeed(float speed) {
		ySpeed = speed;
		return 1;
	}
	float getXSpeed() {
		return xSpeed;
	}
	float getYSpeed() {
		return ySpeed;
	}
	bool getCommand(int com) {
		if ((com == 32 || com == 87 || com == 119)) { // W SPACE
			ySpeed = -5;
		}
		if ((com == 100 || com == 68)) { // D
			hero.setScale(0.2, 0.2);
			xSpeed = 5;
		}
		if ((com == 65 || com == 97)) { // A
			hero.setScale(-0.2, 0.2);
			xSpeed = -5;
		}
		return 1;
	}
	bool update() {
		if (hero.getScale().x < 0) {
			hero.move(-0.1, 0);
		}
		hero.move(xSpeed, ySpeed);
		currentPos = hero.getPosition();
		lastPos = currentPos;
		if (xSpeed > 0) {
			xSpeed -= 0.1;
		}
		if (xSpeed < 0) {
			xSpeed += 0.1;
		}
		if (ySpeed < 1) {
			ySpeed += 0.1;
		}
		if (hero.getPosition().y > 905) {
			hero.setPosition(hero.getPosition().x, 905);
			ySpeed = 0;
		}
		//cout << xSpeed << " " << ySpeed << endl;
		return 1;
	}
	bool draw() {
		window.draw(hero);
		return 1;
	}
};
Hero hero;
class level {
	Texture groundT;
	Image pipeI;
	Texture pipeT;
	vector<Sprite> grounds;
	vector<Sprite> pipes;
	vector<Sprite> pipes2;
	RectangleShape stone;
public:
	level() {
		stone.setPosition(0, 900);
		stone.setFillColor(Color(127, 127, 127));
		stone.setSize({ 100, 100 });
		pipeI.loadFromFile("111111.png");
		pipeI.createMaskFromColor(Color::White);
		pipeT.loadFromImage(pipeI);
		pipeT.setRepeated(1);
		reGenerate();
		groundT.loadFromFile("23424.png");
		groundT.setRepeated(1);
		for (int i = -100; i <= 100; ++i) {
			Sprite temp;
			temp.setTexture(groundT);
			temp.setPosition(3056 * i, 0);
			grounds.push_back(temp);
		}
	}
	bool reGenerate() {
		pipes.resize(0);
		pipes2.resize(0);
		srand(time(0));
		for (int i = -1000; i < 1000; ++i) {
			Sprite temp;
			temp.setTexture(pipeT);
			temp.setScale(1, 1.5);
			temp.setPosition(i * 300, rand() % 250 - 300);
			pipes.push_back(temp);
		}
		for (int i = -1000; i < 1000; ++i) {
			Sprite temp;
			temp.setTexture(pipeT);
			temp.setScale(1, -1.5);
			temp.setPosition(i * 300, 1000 - pipes[i + 1000].getPosition().y);
			pipes2.push_back(temp);
		}
		return 1;
	}
	bool check() { // 126 340
		Vector2f pos = hero.getPosition();
		bool temp = 0;
		if (pos.x+45 > stone.getPosition().x && pos.x+45 < stone.getPosition().x + 3/*stone.getSize().x*/&&hero.hero.getScale().x>0&&pos.y > stone.getPosition().y&&pos.y < stone.getPosition().y+stone.getSize().y) {
			temp = 1;
			//hero.setPosition(hero.lastPos.x, hero.lastPos.y);
			//hero.setXSpeed(0);
		}
		if (pos.y > stone.getPosition().y && pos.y < stone.getPosition().y + stone.getSize().y&&!temp) {
			//hero.setPosition(hero.lastPos.x, hero.lastPos.y);
		}
		if (pos.y < 0) {
			hero.setPosition(-100, 905);
			reGenerate();
		}
		for (int i = 0; i < pipes.size(); ++i) {
			if (pos.x > pipes[i].getPosition().x && pos.x < pipes[i].getPosition().x + 126 && pos.y > pipes[i].getPosition().y && pos.y < pipes[i].getPosition().y + 340 * 1.5) {
				hero.setPosition(-100, 905);
				reGenerate();
			}
		}
		for (int i = 0; i < pipes2.size(); ++i) {
			if (pos.x > pipes2[i].getPosition().x && pos.x < pipes2[i].getPosition().x + 126&&hero.getPosition().y>pipes2[i].getPosition().y-340*1.5-45) {
				hero.setPosition(-100, 905);
				reGenerate();
			}
		}
		return 1;
	}
	bool draw() {
		for (int i = 0; i < grounds.size(); ++i) {
			window.draw(grounds[i]);
		}
		for (int i = 0; i < pipes.size(); ++i) {
			window.draw(pipes[i]);
		}
		for (int i = 0; i < pipes2.size(); ++i) {
			window.draw(pipes2[i]);
		}
		//window.draw(stone);
		return 1;
	}
};
int main()
{
	int x, y;
	Font font;
	font.loadFromFile("my.ttf");
	View Camera;
	level Level;
	while (window.isOpen())
	{ // 168, 408
		x = Mouse::getPosition().x - window.getPosition().x - 5;
		y = Mouse::getPosition().y - window.getPosition().y - 30;
		Camera.setCenter(hero.getPosition().x, 500);
		window.setView(Camera);
		window.clear(Color(245,245,200));



		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				cout << x << " " << y << endl;
				
			}
			if (event.type == sf::Event::TextEntered) { // enter - 13 backspace - 8 - - 45 + - 61
				hero.getCommand(event.text.unicode);
			}
		}
		Level.check();
		hero.update();
		Level.draw();
		hero.draw();
		window.display();
	}
}
