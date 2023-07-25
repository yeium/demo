#include <SFML/Graphics.hpp>
#include<windows.h>
#include<conio.h>
#include<thread>
#include<map>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<math.h>
#include<algorithm>
#include<iostream>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
using namespace std;
using namespace sf;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
typedef BOOL(WINAPI* PROCSETCONSOLEFONT)(HANDLE, DWORD);
PROCSETCONSOLEFONT SetConsoleFont;
string rtx, toward;
CONSOLE_FONT_INFOEX cfi;
sf::Window window(sf::VideoMode(800, 600), "SFML window");
sf::WindowHandle handle = window.getSystemHandle();

bool con = false;
bool sync = false;

int o = 3;
bool focus = true;
string juqing = "几个月前，城市中多出了一块石碑//或者说，所有但凡大一点的都市中央都多出了一块石碑//它们大小相仿，形态却不尽相似，每一块上都有它独特的特征//人们对它们的出现格外惊奇，有的人对它敬而远之，认为此事必有蹊跷//而随着时间的推移，人们便不再害怕它们，甚至在它们的附近建上了旅游景点//只有国家还在重视着它们，甚至派出了多名科研员对它进行研究//但似乎毫无成果，似乎只是一块普通的石头//……[show]//";

int juqingi = 0;

void mouse() {
	

}

wstring stringTowstring(string str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (len == 0)
		return wstring(L"");
	wchar_t* wct = new wchar_t[len];
	if (!wct)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wct, len);
	wstring wstr(wct);
	delete[] wct;
	wct = NULL;
	return wstr;
}
wstring usejuqing;
wstring tojuqing;
int change = 1;
bool background = false;
bool lightground = false;
wstring loadjuqing() {
	string back = "";
	int i, cnt = 0;
	i = juqingi;
	while (1) {
		if (juqingi >= juqing.length())break;
		if (juqing[juqingi] == '/' && juqing[juqingi + 1] == '/')break;
		if (juqing[juqingi] == '[') {
			if (juqing.substr(juqingi + 1, 4) == "show") {
				juqingi += 6;
				background = true;
			}
		}
		else {
			back += juqing[juqingi];
			juqingi++;
			cnt++;
		}
		
	}
	std::cout << back;
	juqingi += 2;
	change = 1;
	usejuqing = stringTowstring(back);
	return stringTowstring(back);
}

void toprint() {
	while (window.isOpen()) {
		int cnt = 0;
		while (change == 0) {

			if (cnt < usejuqing.length()) {
				tojuqing += usejuqing[cnt];
				cnt++;
			}
			Sleep(35);
		}
		tojuqing = L"";
		change = 0;
	}
}

bool check(char c) {
	Sleep(10);
	if (KEY_DOWN(c) == true) return true;
	else return false;
}
void config()
{
	while (window.isOpen()) {
		Sleep(10);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			if (con == true)con = false;
			else con = true;
			Sleep(100);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (sync == false) {
				sync = true;
				window.setVerticalSyncEnabled(true);
			}
			else {
				sync = false;
				window.setVerticalSyncEnabled(false);
			}
			Sleep(100);
		}
	}

}
float x, y;
int lastalpha;
int cnt[5];
void control() {
	while (window.isOpen()) {
		Sleep(1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cnt[0] += 2;
			if (cnt[0] < 20)x--;
			else if (cnt[0] < 30)x -= 2;
			else if (cnt[0] < 40)x -= 3;
			else x -= 4, cnt[0]--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			cnt[1] += 2;
			if (cnt[1] < 20)x++;
			else if (cnt[1] < 30)x += 2;
			else if (cnt[1] < 40)x += 3;
			else x += 4, cnt[1]--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			cnt[2] += 2;
			if (cnt[2] < 20)y--;
			else if (cnt[2] < 30)y -= 2;
			else if (cnt[2] < 40)y -= 3;
			else y -= 4, cnt[2]--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			cnt[3] += 2;
			if (cnt[3] < 20)y++;
			else if (cnt[3] < 30)y += 2;
			else if (cnt[3] < 40)y += 3;
			else y += 4, cnt[3]--;
		}
		o = cnt[0];
		for (int i = 0; i < 4; i++) {
			cnt[i] -= 1;
			if (cnt[i] < 0)cnt[i] = 0;
			if (cnt[i] > o)o = cnt[i];
		}
		if (o < 3)o = 3;
		if (x < 0)x = 0;
		if (x > 1080)x = 1080;
		if (y < 0)y = 0;
		if (y > 520)y = 520;
	}
}
sf::Clock clockk; // starts the clock
bool checkleft() {

	sf::Time elapsed1 = clockk.getElapsedTime();
	if (elapsed1.asMilliseconds() > 500&&focus==true) {
		clockk.restart();
		return true;
	}
	else return false;
}
int alpha = 0;
void CG() {
	if (lightground == false) {
		alpha-=2;
	}
	else alpha+=2;
	if (alpha > 255)alpha = 255;
	if (alpha < 0)alpha = 0;
}

void render() {
	sf::Texture texture;
	if (!texture.loadFromFile("wuxiang.jpg")) {

	}
	
	sf::Texture conti;
	if (!conti.loadFromFile("图片2.png")) {

	}
	sf::Texture balll;
	if (!balll.loadFromFile("1.jpg")) {

	}
	sf::Sprite cont;
	cont.setTexture(conti);
	cont.setScale(sf::Vector2f(0.7f, 0.70f)); // absolute scale factor	
	cont.setPosition(1130, 620);

	sf::Font font;
	if (!font.loadFromFile("simhei.ttf"))
	{
		// error...
	}
	sf::Text text;
	sf::Text shadowtext;
	// select the font
	shadowtext.setFont(font);
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString(L"");
	shadowtext.setString(L"");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	shadowtext.setCharacterSize(24);
	shadowtext.setString(L"");
	// set the color
	text.setFillColor(sf::Color::White);
	shadowtext.setFillColor(sf::Color::Black);
	// set the text style
	text.setPosition(200, 600);
	shadowtext.setPosition(202, 602);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.65f, 0.65f)); // absolute scale factor
	sprite.setColor(Color(255,255 , 255, 0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Demo: Tomorrow  Ver. Alpha 0.003", sf::Style::Titlebar, settings);
	sf::CircleShape shape(100.f, o);
	shape.setFillColor(sf::Color::Green);
	sf::CircleShape sha(100.f);
	sha.setFillColor(sf::Color::Yellow);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{

		sf::Event event {};
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				std::cout << "good byyyye" << std::endl;
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "height:" << event.size.height << std::endl;
				std::cout << "weight:" << event.size.width << std::endl;
				break;
			case sf::Event::LostFocus:
				std::cout << "hei! what are you doing!\n";
				focus = false;
				break;
			case sf::Event::GainedFocus:
				std::cout << "ok.." << std::endl;
				focus = true;
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == 57)if (checkleft())loadjuqing();
				std::cout << event.key.code << std::endl;
				//                  std::boolalpha(std::cout);
				//                  std::cout << "the escape key was pressed" << std::endl;
				//                  std::cout << "control:" << event.key.control << std::endl;
				//                  std::cout << "alt:" << event.key.alt << std::endl;
				//                  std::cout << "shift:" << event.key.shift << std::endl;
				//                  std::cout << "system:" << event.key.system << std::endl;
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128)
					std::cout << "ASCII character typed :" << static_cast<char>(event.text.unicode) << std::endl;
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					std::cout << "wheel type: vertical" << std::endl;
				else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
					std::cout << "wheel type: Horizontal" << std::endl;
				else
					std::cout << "while type: unknown" << std::endl;
				std::cout << "wheel delta:" << event.mouseWheelScroll.delta << std::endl;
				std::cout << "wheel x:" << event.mouseWheelScroll.x << std::endl;
				std::cout << "wheel y:" << event.mouseWheelScroll.y << std::endl;
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right)
					std::cout << "right button pressed" << std::endl;
				else if (event.mouseButton.button == sf::Mouse::Left)
					std::cout << "left button pressed" << std::endl;
				else if (event.mouseButton.button == sf::Mouse::Middle)
					std::cout << "middle button pressed" << std::endl;
				std::cout << "mouse x:" << event.mouseButton.x << std::endl;
				std::cout << "mouse y:" << event.mouseButton.y << std::endl;
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Right)
					std::cout << "right button Released" << std::endl;
				else if (event.mouseButton.button == sf::Mouse::Left)
					std::cout << "left button Released" << std::endl;
				else if (event.mouseButton.button == sf::Mouse::Middle)
					std::cout << "middle button Released" << std::endl;
				std::cout << "mouse x:" << event.mouseButton.x << std::endl;
				std::cout << "mouse y:" << event.mouseButton.y << std::endl;
				break;
			case sf::Event::MouseMoved:
				//                  std::cout << "new mouse x " << event.mouseMove.x << std::endl;
				//                  std::cout << "new mouse y " << event.mouseMove.y << std::endl;
			default:
				break;
			}
		}
		if (background == true) {
			background = false;
			if (lightground == false) {
				lightground = true;
			}
			else {
				lightground = false;
			}
		}
		CG();
		if (alpha != lastalpha) {
			lastalpha = alpha;
			sprite.setColor(Color(255, 255, 255, alpha));
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (checkleft())loadjuqing();
		}
		text.setString(tojuqing);
		shadowtext.setString(tojuqing);
		sf::CircleShape shape(100.f, o);
		//shape.setTexture(balll);
		shape.setPosition(x, y);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		window.draw(sprite);
		//window.draw(shape);
		window.draw(shadowtext);
		window.draw(text);
		sf::Time elapsed1 = clockk.getElapsedTime();
		if (elapsed1.asMilliseconds() > 500) {
			window.draw(cont);
		}
		window.display();

	}
}

int main()
{
	thread toprintt(toprint);
	thread configg(config);  //实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
	thread renderr(render);
	thread mov(control);
	toprintt.join();
	configg.join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
	renderr.join();
	mov.join();
	return 0;
}