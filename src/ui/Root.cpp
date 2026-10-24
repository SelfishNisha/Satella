#include "ui.h"

void Root() {
  App app;

  part<Vertical> root = std::make_shared<Vertical>();
  root->add(Header());

  app.run(root);
}