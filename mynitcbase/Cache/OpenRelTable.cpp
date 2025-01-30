#include "OpenRelTable.h"
#include <cstring>
#include <stdlib.h>

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
  }

  /************ Setting up Relation Cache entries ************/

  /**** setting up Relation Catalog relation in the Relation Cache Table****/

  RecBuffer relCatBlock(RELCAT_BLOCK);

  Attribute relCatRecord[RELCAT_NO_ATTRS];
  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

  struct RelCacheEntry relCacheEntryForRelCat;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntryForRelCat.relCatEntry);
  relCacheEntryForRelCat.recId.block = RELCAT_BLOCK;
  relCacheEntryForRelCat.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntryForRelCat;

  /**** setting up Attribute Catalog relation in the Relation Cache Table ****/
  
  Attribute attrCatInRelCat[RELCAT_NO_ATTRS];
  relCatBlock.getRecord(attrCatInRelCat, RELCAT_SLOTNUM_FOR_ATTRCAT);

  struct RelCacheEntry relCacheEntryForAttrCat;
  RelCacheTable::recordToRelCatEntry(attrCatInRelCat, &relCacheEntryForAttrCat.relCatEntry);
  relCacheEntryForAttrCat.recId.block = RELCAT_BLOCK;
  relCacheEntryForAttrCat.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

  RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = relCacheEntryForAttrCat;


  /* setting up students relation in rel cache table*/

    Attribute studentsInRelCat[RELCAT_NO_ATTRS];
    relCatBlock.getRecord(studentsInRelCat, 2);

    struct RelCacheEntry relCacheEntryForStudents;
    RelCacheTable::recordToRelCatEntry(studentsInRelCat, &relCacheEntryForStudents.relCatEntry);
    relCacheEntryForStudents.recId.block = RELCAT_BLOCK;
    relCacheEntryForStudents.recId.slot = 2;

    RelCacheTable::relCache[2] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[2]) = relCacheEntryForStudents;
  











  /************ Setting up Attribute cache entries ************/
  
  /**** setting up Relation Catalog relation in the Attribute Cache Table ****/

  RecBuffer attrCatBlock(ATTRCAT_BLOCK);
  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];

  struct AttrCacheEntry * prev = nullptr;
  struct AttrCacheEntry * head = nullptr;
  for(int i=0; i<=5; i++){
    attrCatBlock.getRecord(attrCatRecord, i);
    struct AttrCacheEntry *attrCacheEntry = (struct AttrCacheEntry *)malloc(sizeof(AttrCacheEntry));
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &(attrCacheEntry->attrCatEntry) );
    (attrCacheEntry->recId).block = ATTRCAT_BLOCK;
    (attrCacheEntry->recId).slot = i;

    if(prev) prev->next = attrCacheEntry;
    if(i==5) attrCacheEntry->next = nullptr;
    if(i==0) head = attrCacheEntry;

    prev = attrCacheEntry;
  }

  AttrCacheTable::attrCache[RELCAT_RELID] = head;

  /**** setting up Attribute Catalog relation in the Attribute Cache Table ****/

  prev = nullptr;
  head = nullptr;
  for(int i=6; i<=11; i++){
    attrCatBlock.getRecord(attrCatRecord, i);
    struct AttrCacheEntry *attrCacheEntry = (struct AttrCacheEntry *)malloc(sizeof(AttrCacheEntry));
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &(attrCacheEntry->attrCatEntry) );
    (attrCacheEntry->recId).block = ATTRCAT_BLOCK;
    (attrCacheEntry->recId).slot = i;

    if(prev) prev->next = attrCacheEntry;
    if(i==11) attrCacheEntry->next = nullptr;
    if(i==6) head = attrCacheEntry;

    prev = attrCacheEntry;
  }

  AttrCacheTable::attrCache[ATTRCAT_RELID] = head;
  
  /* setting up students in attr cache table */

  prev = nullptr;
  head = nullptr;
  for(int i=12; i<=15 ; i++){
    attrCatBlock.getRecord(attrCatRecord, i);

    char name[] = "Students";
    if(strcmp(name, attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal) == 0){
      struct AttrCacheEntry *attrCacheEntry = (struct AttrCacheEntry *)malloc(sizeof(AttrCacheEntry));
      AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &(attrCacheEntry->attrCatEntry) );
      (attrCacheEntry->recId).block = ATTRCAT_BLOCK;
      (attrCacheEntry->recId).slot = i;

      if(prev) prev->next = attrCacheEntry;
      if(i==15) attrCacheEntry->next = nullptr;
      if(i==12) head = attrCacheEntry;

      prev = attrCacheEntry;
    }
  }

  AttrCacheTable::attrCache[2] = head;

}

OpenRelTable::~OpenRelTable() {
  for(int i=0; i<MAX_OPEN; i++){
    free(RelCacheTable::relCache[i]);
    struct AttrCacheEntry* node = AttrCacheTable::attrCache[i];
    while(node){
      struct AttrCacheEntry* temp = node;
      node = node->next;
      free(temp);
    }
  }
}