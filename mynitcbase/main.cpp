#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;
  
  for(int i=0; i<=2; i++){
    struct RelCatEntry relCatEntry;
    RelCacheTable::getRelCatEntry(i, &relCatEntry);
    printf("Relation: %s\n", relCatEntry.relName);

    for(int j=0; j<relCatEntry.numAttrs; j++){
      struct AttrCatEntry attrCatEntry;
      AttrCacheTable::getAttrCatEntry(i, j, &attrCatEntry);
      const char *attrType = (attrCatEntry.attrType == NUMBER) ? "NUM" : "STR";
      printf("  %s: %s\n", attrCatEntry.attrName, attrType);
    }
  }

  return 0;
}