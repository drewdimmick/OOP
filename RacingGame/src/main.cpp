#include <cmath>

#include <SFML/Graphics.hpp>

#include "../include/car.h"
using namespace sf;

struct eventListener
{
  // Keyboard Events
  virtual void on_key_press(sf::Event::KeyEvent) {}
  virtual void on_key_release(sf::Event::KeyEvent) {}

  // Window Events
  virtual void on_close() {}
  virtual void on_gain_focus() {}
  virtual void on_lose_focus() {}
  virtual void on_resize() {}
};

struct listenerNotifier
{
  listenerNotifier(sf::Window& w) : window(&w) { }

  // A vector of listeners to notify
  std::vector<eventListener*> listeners;

  // The window that we can poll for events
  sf::Window* window;

  void listen(eventListener& l)
  {
    listeners.push_back(&l);
  }

  // Notify listeners of queued events
  void poll()
  {
    sf::Event e;
    while(window->pollEvent(e))
    {
      process(e);
    }
  }

  // Notify listeners of a single event
  void process(sf::Event const& e)
  {
    switch(e.type)
    {
      case Event::Closed:
        return notify([e](eventListener* l) {l->on_close();});
      case Event::Resized:
        return notify([e](eventListener* l) {l->on_resize();});

      case Event::KeyPressed:
        return notify([e](eventListener* l) {l->on_key_press(e.key);});
      case Event::KeyReleased:
        return notify([e](eventListener* l) {l->on_key_release(e.key);});

      default:
        break;
    }
  }

  template <typename F>
  void notify(F fn)
  {
    for(eventListener* l : listeners)
    {
      fn(1);
    }
  }
};

// Container for graphical resources
struct racingGame_graphics
{
  racingGame_graphics()
  {
    textures[0].loadFromFile("images/background.png");
    textures[1].loadFromFile("images/car.png");
    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
  }

  // Array for loaded textures
  sf::Texture textures[2];

  // Drawable sprites
  sf::Sprite background(textures[0]);
  sf::Sprite sCar(textures[1]);

  background.scale(2,2);
  sCar.setOrigin(22, 22);
};

struct racingGame_app : eventListener
{
  racingGame_app()
    : window(VideoMode(640, 480), "Car Racing Game!")
  {
    window.setFramerateLimit(60);
  }

  // Returns true if app is open
  bool is_open() const { return window.isOpen(); }

  // Closes the app
  void on_close() override
  {
    window.close();
  }

  int N = 5;
  Car car[N];
  for(int i = 0; i < N; i++) 
  {
    car[i].x = 300 + i * 50;
    car[i].y = 1700 + i * 80;
    car[i].speed = 7 + i;
  }

  float speed = 0, angle = 0;
  float maxSpeed = 12.0;
  float acc = 0.2, dec = 0.3;
  float turnSpeed = 0.08;
  float R = 22;

  int offsetX = 0, offsetY = 0;

  void on_key_press(sf::Event::KeyEvent e) override
  {
    bool Up = 0, Right = 0, Down = 0, Left = 0;
    if (Keyboard::isKeyPressed(Keyboard::W)) // Changed these all to WASD 
      Up = 1;
    if (Keyboard::isKeyPressed(Keyboard::D)) // instead of the arrow keys
      Right = 1;
    if (Keyboard::isKeyPressed(Keyboard::S))
      Down = 1;
    if (Keyboard::isKeyPressed(Keyboard::A))
      Left = 1;

    // car movement
    if (Up && speed < maxSpeed) {
      if (speed < 0)
        speed += dec;
      else
        speed += acc;
    }

    if (Down && speed > -maxSpeed) {
      if (speed > 0)
        speed -= dec;
      else
        speed -= acc;
    }

    if (!Up && !Down) {
      if (speed - dec > 0)
        speed -= dec;
      else if (speed + dec < 0)
        speed += dec;
      else
        speed = 0;
    }

    if (Right && speed != 0)
      angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0)
      angle -= turnSpeed * speed / maxSpeed;

    car[0].speed = speed;
    car[0].angle = angle;

    for (int i = 0; i < N; i++)
      car[i].move();
    for (int i = 1; i < N; i++)
      car[i].findTarget();
  }

  void onCollision()
  {
    // collision
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int dx = 0, dy = 0;
        while (dx * dx + dy * dy < 4 * R * R) {
          car[i].x += dx / 10.0;
          car[i].x += dy / 10.0;
          car[j].x -= dx / 10.0;
          car[j].y -= dy / 10.0;
          dx = car[i].x - car[j].x;
          dy = car[i].y - car[j].y;
          if (!dx && !dy)
            break;
        }
      }
    }
  }

  void draw()
  {

    window.clear(Color::White);

    if (car[0].x > 320)
      offsetX = car[0].x - 320;
    if (car[0].y > 240)
      offsetY = car[0].y - 240;

    graph.background.setPosition(-offsetX, -offsetY);
    window.draw(graph.background);

    Color colors[10] = {
      Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White
    };

    for (int i = 0; i < N; i++) {
      graph.sCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
      graph.sCar.setRotation(car[i].angle * 180 / 3.141593);
      graph.sCar.setColor(colors[i]);
      window.draw(graph.sCar);
    }

    window.display();

  }

  // Container for graphics
  racingGame_graphics graph;

  // The game window
  sf::RenderWindow window;
};

int
main()
{
  // Create the app data window
  racingGame_app app;

  // Construct the event loop and listeners
  listenerNotifier events(app.window);
  events.listen(app);

  while(app.is_open())
  {
    // Poll for events
    events.poll();

    // Update game state
    app.onCollision();

    // Render the game
    app.draw();
  }

  return 0;
}