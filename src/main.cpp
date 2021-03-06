// Robert Gee
// 2021

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

// make text with strikethrough codes embedded or something like that. Pretty cool looking.
std::string strikethrough(const std::string& text) { //https://stackoverflow.com/a/33154446
  std::string result;
  int count = 0;
  for (auto ch : text) {
    if(count > 0) {
      result.append(u8"\u0336");
    }
    count += 1;
    result.push_back(ch);
  }
  return result;
}

// function to return the default file path
// todo: support current dir todo-lists
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
      bool done = false; // if the item has been completed or not.
      if (item[0] == 'd') { // d at beginnning denotes it has been done.
        done = true;
      }
      item.erase(0, 1); // erase the first char as it's just an internal marker for done or not done.
      if(!done) {
        std::cout << count << ": " << item << std::endl;
      } else {
        std::cout << count << ": " << strikethrough(item) << std::endl;
      }
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
  // just open file in append mode.
  // then add the data to the file
  // n used before data to denote (n)ot done
  std::fstream itemsFile;
  itemsFile.open(getFilePath(), std::ios::app);
  if(itemsFile.is_open()) {
    for(int i = 2; i < argc; i++) {
      itemsFile << "n" << argv[i] << std::endl;
    }
  }
  itemsFile.close();
}

void completeItem(int argc, int index) {
  // read the files into a list.
  // alter the given index
  // write back to the file.
  std::fstream itemsFile;
  itemsFile.open(getFilePath());
  if(itemsFile.is_open()) {
    std::string item;
    std::vector<std::string> items;
    while(std::getline(itemsFile, item)) {
      items.push_back(item);
    }

    itemsFile.close();
    itemsFile.open(getFilePath(), std::ios::out | std::ios::trunc);

    if(items.size() > 0) {
      // first change the first element to a d. this indicates it is done. yeah yeah, it's dumb but whatevs.
      items[index].erase(0, 1); // erase the first element.
      items[index] = "d" + items[index];

      // now write the items back to the file.
      for(int i = 0; i < items.size(); i++) {
        itemsFile << items[i] << std::endl;
      }
      itemsFile.close();
    }
  }
}

void completeItems(int argc, char *argv[]) {
  for(int i = 2; i < argc; i++) {
    completeItem(argc, strtol(argv[i], NULL, 10));
  }
}

// remove a single item.

void removeItem(int argc, char *argv[]) {
  //basically the same as complete item but we will just not re-write the specified index to the file.
  std::fstream itemsFile;
  itemsFile.open(getFilePath());
  if(itemsFile.is_open()) {
    std::string item;
    std::vector<std::string> items;
    while(std::getline(itemsFile, item)) {
      items.push_back(item);
    }

    itemsFile.close(); // close and re-open
    itemsFile.open(getFilePath(), std::ios::out | std::ios::trunc);

    if(items.size() > 0) {
      // now write the items back to the file.
      // but check that the we are not writing any of the given indexs
      for(int i = 0; i < items.size(); i++) {
        bool write = true; // flag to set if i is a given index.
        for(int x = 2; x < argc; x++) { // given indexs start at argv[2]
          if(strtol(argv[x], NULL, 10) == i) { // if argv[x] == i then i is a given index
            write = false;
          }
        }
        if(write) { // if write is still true then i is not a given index and we should write this line. 
          itemsFile << items[i] << std::endl;
        }
      }
      itemsFile.close();
    }
  }
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

  if(command.compare("done") == 0) {
    completeItems(argc, argv);
  }

  if(command.compare("rm") == 0) {
    removeItem(argc, argv);
  }
}

int main(int argc, char *argv[]) {
  handleInput(argc, argv);

  return 0;
}
