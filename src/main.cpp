// Robert Gee
// 2021

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

std::string strikethrough(const std::string& text) { //https://stackoverflow.com/a/33154446
  std::string result;
  for (auto ch : text) {
    result.append(u8"\u0336");
    result.push_back(ch);
  }
  return result;
}

// function to return the default file path
// todo support current dir todo-lists
std::string getFilePath() {
  std::string path = getenv("HOME");
  path += "/.todo-items.txt";

  return path;
}

// prints the items in the default todo list
void printItems() {
  std::ifstream itemsFile;
  itemsFile.open(getFilePath());
  if(itemsFile.is_open()) {
    std::string item;
    int count = 0;
    while(std::getline(itemsFile, item)) {
      std::cout << count << ": " << item << std::endl;
      count += 1;
    }
  }
  itemsFile.close();
}

void showHelp() {
  // todo: add code
  std::cout << "help text goes here" << std::endl;
}

void addItem(int argc, char *argv[]) {
  // read all the items to a vector.
  std::fstream itemsFile;
  itemsFile.open(getFilePath(), std::ios::app);
  if(itemsFile.is_open()) {
    for(int i = 2; i < argc; i++) {
      itemsFile << argv[i] << std::endl;
    }
  }
  itemsFile.close();
}

// handles the user input.
// basically reads and redirects.
void handleInput(int argc, char *argv[]) {
  if (argc == 1) {
    printItems();
    return;
  }
  // just evaluate the first argument that's not the program name
  std::string command = argv[1];

  if (command.compare("-h") == 0) {
    showHelp();
    return;
  }

  if(command.compare("add") == 0) {
    addItem(argc, argv);
    return;
  }
}

int main(int argc, char *argv[]) {
  handleInput(argc, argv);

  return 0;
}
