#pragma once
#include "../std.hpp"

namespace src::gui {

class IDrawable {
public:
  virtual ~IDrawable() {}

  virtual void draw() = 0;
};

typedef std::shared_ptr<IDrawable> DrawablePtr;

};