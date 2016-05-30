
#include "DescriptorOBJ.hpp"

std::list<Point*> *DescriptorOBJ::readPoints(const std::vector<Point*> *points, const char *line) {
  int i;
  std::list<Point*> *readedPoints = new std::list<Point*>;
  // check all points in line
  for (i = 0; line[i]; i++) {
    if (line[i] >= '0' && line[i] <= '9') {
      char num[20];
      int j;
      // copy number to num
      for (j = 0; line[i]; i++) {
        if (line[i] == ' ' || line[i] == '/')
          break;
        num[j++] = line[i];
      }
      // ignore texture points (slash /) in faces
      while (line[i] != ' ' && line[i] != '\0') {
        i++;
      }
      num[j] = '\0';
      readedPoints->push_back((Point*)points->at(atoi(num) - 1)->clone());
      // Last number case
      if (line[i] == '\0') {
        break;
      }
    }
  }
  return readedPoints;
}

void DescriptorOBJ::save(DisplayFile *df, const char *fileName) {
  if (fileName == NULL || df == NULL) {
    return;
  }
  if (fileName[0] == '\0') {
    return;
  }
  FILE *file = fopen(fileName,"w");
  df->save(file);
  fclose(file);
}

std::list<Object*> *DescriptorOBJ::load(const char *fileName) {
  std::list<Object*> *objects = new std::list<Object*>;
  if (fileName == NULL) {
    return objects;
  }
  if (fileName[0] == '\0') {
    return objects;
  }
  FILE *file = fopen(fileName, "r");
  std::vector<Point*> *pointsList = new std::vector<Point*>;
  Object *tmpObj;
  char name[150];
  char tmpLine[512];
  int ch;
  while ( (ch = fgetc(file) ) != EOF) {
    int i = 0;
    // if comment discard line
    if (ch == '\n') {
      continue;
    }
    if (ch == '#') {
      while ( (ch = fgetc(file) ) != '\n') {
        if (ch == EOF) {
          break;
        }
      }
      continue;
    }
    // copy line
    tmpLine[i++] = ch;
    while ( (ch = fgetc(file) ) != '\n') {
      if (ch == EOF) {
        break;
      }
      if (ch == '#') {
        while ( (ch = fgetc(file) ) != '\n') {
          if (ch == EOF) {
            break;
          }
        }
        break;
      }
      if (ch == '.')
        ch = ',';
      tmpLine[i++] = ch;
    }
    tmpLine[i] = '\0';
    // if object name use it
    if (tmpLine[0] == 'o') {
      sscanf(tmpLine, "o %s", name);
    }
    // if vertex get points
    if (tmpLine[0] == 'v' && tmpLine[1] == ' ') {
      float x, y, z, nil;
      sscanf(tmpLine, "v %f %f %f %f", &x, &y, &z, &nil);
      pointsList->push_back(new Point((std::string*) NULL, x, y, z));
    }
    if (tmpLine[0] == 'p' && tmpLine[1] == ' ') {
      std::list<Point*> *points;
      points = readPoints(pointsList, tmpLine);
      tmpObj = points->front();
      delete points;
      GUI::addToListBox(std::string(name));
      objects->push_back(tmpObj);
    }
    if (tmpLine[0] == 'l' && tmpLine[1] == ' ') {
      std::list<Point*> *linePoints;
      linePoints = readPoints(pointsList, tmpLine);
      tmpObj = new Line(name, linePoints->front(), linePoints->back());
      delete linePoints;
      GUI::addToListBox(std::string(name));
      objects->push_back(tmpObj);
    }
    if (tmpLine[0] == 'f' && tmpLine[1] == ' ') {
      std::list<Point*> *polygonPoints;
      polygonPoints = readPoints(pointsList, tmpLine);
      tmpObj = new Polygon(name, polygonPoints);
      GUI::addToListBox(std::string(name));
      objects->push_back(tmpObj);
    }
    if (tmpLine[0]  == 'c' && tmpLine[1] == ' ') {
      std::list<Point*> *curvePoints;
      curvePoints = readPoints(pointsList, tmpLine);
      tmpObj = new Curve(name, curvePoints);
      GUI::addToListBox(std::string(name));
      objects->push_back(tmpObj);
    }
  }
  std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  delete pointsList;
  fclose(file);
  return objects;
}
