#include <fmt/format.h>
#include <unistd.h>
#include <iostream>
#include <greeter/greeter.h>
#include <CXXStateTree/StateTree.hpp>
using namespace CXXStateTree;

using namespace greeter;

Greeter::Greeter(std::string _name) : name(std::move(_name)) {}

std::string Greeter::greet(LanguageCode lang) const {
  switch (lang) {
    default:
    case LanguageCode::EN:
      return fmt::format("Hello, {}!", name);
    case LanguageCode::DE:
      return fmt::format("Hallo {}!", name);
    case LanguageCode::ES:
      return fmt::format("¡Hola {}!", name);
    case LanguageCode::FR:
      return fmt::format("Bonjour {}!", name);
    case LanguageCode::ZH:
      return fmt::format("{}您好！", name);
  }

  demo_state_machine();
}

void demo_state_machine() {
  auto machine = Builder()
      .initial("Idle")
  .state("Idle", [](State& s) {
    s.on("Start", "Running", nullptr, []() {
      std::cout << "Idle --> Running" << std::endl;
    });
  })
  .state("Running", [](State& s) {
    s.on("Stop", "Idle", nullptr, []() {
      std::cout << "Running --> Idle" << std::endl;
    });
  })
  .build();

  machine.send("Start");
  std::cout << "Running for a while ..." << std::endl;
  sleep(2);
  machine.send("Stop");
}
