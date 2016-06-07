
#include "DescriptorOBJ.hpp"

std::list<Point*> *DescriptorOBJ::readPoints(const std::vector<Point*> *points, const char *line) {
  std::list<Point*> *readedPoints = new std::list<Point*>;
  std::list<int> *readedPointsNumber = readPointsNumber(line);
  std::list<int>::iterator it = readedPointsNumber->begin();
  for (; it != readedPointsNumber->end(); it++) {
    readedPoints->push_back((Point*)points->at(*it)->clone());
  }
  readedPointsNumber->clear();
  delete readedPointsNumber;
  return readedPoints;
}

std::list<int> *DescriptorOBJ::readPointsNumber(const char *line) {
  int i;
  std::list<int> *readedPoints = new std::list<int>;
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
      readedPoints->push_back(atoi(num) - 1);
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
  std::list<Object*> *objTempList = NULL;
  if (fileName == NULL) {
    return objects;
  }
  if (fileName[0] == '\0') {
    return objects;
  }
  FILE *file = fopen(fileName, "r");
  std::vector<Point*> *pointsList = new std::vector<Point*>;
  std::list<std::pair<int,int>> *edgeList = new std::list<std::pair<int,int>>;
  Object *tmpObj = NULL;
  char name[150];
  char tmpLine[512];
  int ch;
  bool has3D = false;
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
      if (ch == ',')
        ch = '.';
      tmpLine[i++] = ch;
    }
    tmpLine[i] = '\0';
    // if object name use it
    if (tmpLine[0] == 'o') {
      if (objTempList == NULL) {
        tmpObj = new Object3D(name, objTempList);
        GUI::addToListBox(std::string(name));
        objects->push_back(tmpObj);
        tmpObj = NULL;
      }
      objTempList = new std::list<Object*>;
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
      tmpObj = points->front()->clone();
      GUI::addToListBox(std::string(name));
      objTempList->push_back(tmpObj);
      tmpObj = NULL;
      delete points;
    }
    if (tmpLine[0] == 'l' && tmpLine[1] == ' ') {
      std::list<Point*> *linePoints;
      linePoints = readPoints(pointsList, tmpLine);
      tmpObj = new Line(name, (Point*)linePoints->front()->clone(), (Point*)linePoints->back()->clone());
      GUI::addToListBox(std::string(name));
      objTempList->push_back(tmpObj);
      tmpObj = NULL;
      delete linePoints;
    }
    if (tmpLine[0] == 'f' && tmpLine[1] == ' ') {
      std::list<Point*> *points, *clonedPts;
      clonedPts = new std::list<Point*>;
      points = readPoints(pointsList, tmpLine);
      std::list<Point*>::iterator it = points->begin();
      it++;
      for (; it != points->end(); it++) {
        clonedPts->push_back((Point*)(*it)->clone());
      }
      objTempList->push_back(new Polygon((const char *)NULL, clonedPts));
      delete points;
    }
    if (tmpLine[0]  == 'c' && tmpLine[1] == ' ') {
      std::list<Point*> *points, *clonedPts;
      clonedPts = new std::list<Point*>;
      points = readPoints(pointsList, tmpLine);
      std::list<Point*>::iterator it = points->begin();
      it++;
      for (; it != points->end(); it++) {
        clonedPts->push_back((Point*)(*it)->clone());
      }
      objTempList->push_back(new Curve((const char *)NULL, clonedPts));
      tmpObj = NULL;
    }
  }
  tmpObj = new Object3D(name, objTempList);
  GUI::addToListBox(std::string(name));
  objects->push_back(tmpObj);
  tmpObj = NULL;
#if 0
  std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  delete pointsList;
#endif
  fclose(file);
  return objects;
}
