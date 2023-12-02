#include <Window.h>

namespace gol {

Window::Window(const uint iWidth, const uint iHeight):
  width_(iWidth), height_(iHeight), window_(sf::VideoMode(iWidth, iHeight), ""),
  eventHandlerThread_(&Window::handleEvents, this)
  {
    ::XInitThreads();
  }

void Window::handleEvents(void) {
  while (this->is_open()) {
    sf::Event event;
    while (this->get_event(event)) {
      this->handle_event(event);
    }
  }
}

bool Window::draw_cell(const uint iCoordX, const uint iCoordY) {
  if ((iCoordX < this->width_) && (iCoordY < this->height_)) {
    sf::RectangleShape rectangle(sf::Vector2f(10, 10));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(iCoordX, iCoordY);
    this->window_.draw(rectangle);
  }
  return false;  
}

bool Window::display() {
  this->window_.display();
  return false;
}

bool Window::is_open(void) const {
  return this->window_.isOpen();
}

bool Window::resize(const uint iWidth, const uint iHeight) {
  if ((iWidth > 0) && (iHeight > 0)) {
    this->window_.setSize(sf::Vector2u(iWidth, iHeight));
    return true;
  }
  return false;
}

bool Window::close(void) {
  if (this->is_open()) {
    this->window_.close();
    return true;
  }
  return false;
}

bool Window::get_event(sf::Event& ioEvent) {
  return this->window_.pollEvent(ioEvent);
}

bool Window::handle_event(const sf::Event& iEvent) {
  bool handledEvent = false;
  switch (iEvent.type) {
  case sf::Event::Closed:
    handledEvent = true;
    this->close();
    break;
  default:
    break;
  }
  return handledEvent;
}

Window::~Window() {
  this->close();
  this->eventHandlerThread_.join();
}

}