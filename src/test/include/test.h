/** 
 *
 */


#ifndef GOL_WINDOW_H
#define GOL_WINDOW_H


#include <thread>

#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>

namespace gol {

class Window {
  using position = std::pair<int, int>;

  public:
    Window(const uint iWidth, const uint iHeight );

    void handleEvents(void);

    bool draw_cell(const uint iCoordX, const uint iCoordY);

    bool display(void);

    bool resize(const uint iWidth, const uint iHeight);

    bool close(void);

    bool get_event(sf::Event& iEvent);

    bool handle_event(const sf::Event& iEvent);

    bool is_open(void) const;

    ~Window();

  private:
    uint width_;
    uint height_;

    sf::RenderWindow window_;
    std::thread eventHandlerThread_;
};

}

#endif // GOL_WINDOW_H
