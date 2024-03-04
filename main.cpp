#include <ctime>
#include <iomanip>
#include <sstream>

#include <unistd.h>

#include <iostream>

void on_ctrl_c(int s)
{
  std::cout << "Cancelling...";
  exit(0);
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " " << "[time]" << std::endl;
    return 1;
  }
  
  long now = time(0);
  long expires = now + std::atoi(argv[1]);

  std::cout << "Timer started!" << std::endl;
  while (expires > now)
  {
    now = time(0);
    long duration = expires - now;

    std::ostringstream oss;
    long hours = duration / 3600; // 3600 seconds in an hour
    long minutes = (duration % 3600) / 60; // 60 seconds in a minute
    long seconds = duration % 60;
    
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Time Left:" << std::endl;
    std::cout << oss.str() << std::endl;
    std::cout << std::endl << "^C: Cancels the timer" << std::endl;

    signal(SIGINT, on_ctrl_c);

    usleep(0.1 * 1000000);
  }

  std::cout << "Times up!";
  return 0;
}
