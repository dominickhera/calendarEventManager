/*

 * CIS2750 F2017

 * Assignment 3

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

 * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, which I took

 * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

 * my current CIS2750 professor, Denis Nikitenko.

 */

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "LinkedListAPI.h"
#include "CalendarParser.h"

Calendar* initializeCalendar();
void manualCalInit(Calendar** obj, char* PRODID);
void manualEventInit(Calendar** obj, char* uid, char* date, char* timeVal);
int getEventListSize(const Calendar* obj);
int getPropertyListSize(const Calendar* obj);
char* printSummary(const Calendar* eventPointer);
Event* initializeEvent(char* date, char* timeVal, char* UTC, char* dateTwo, char* timeValTwo, char* UTCTwo);
Property* initializeProperty(char* propName, char* propDescr);
Alarm* initializeAlarm(char* action, char* trigger);
void  tDestroy(void *data);
char * tPrint(void *toBePrinted);
int tCompare(const void * one, const void * two);

ICalErrorCode createCalendar(char* fileName, Calendar** obj)
{
    FILE *fp;
    char line[256];
    char lineStorage[500][500];
    char eventPropNameStorage[256][200];
    char eventPropDscrStorage[256][500];
    char alarmPropNameStorage[500][200];
    char alarmPropDscrStorage[500][500];
    char calendarPropNameStorage[256][200];
    char calendarPropDscrStorage[256][500];
    char alarmActionStorage[256][200];
    char alarmTriggerStorage[256][500];
    char eventUIDStorage[1000][1000];
    char eventDateStorage[256][256];
    char eventDSTARTDateStorage[256][256];
    char eventTimeStorage[256][256];
    char eventDSTARTTimeStorage[256][256];
    char eventUTCStorage[256][256];
    char eventDSTARTUTCStorage[256][256];
    char UIDStorage[256];
    char VersionStorage[256];
    char PROIDStorage[256];
    char DSTAMPStorage[256];
    char DSTARTStorage[256];
    char triggerStorage[256];
    char actionStorage[200];
    char newOtherTempStorage[1000];
    float tempVersion = 0;
    char newTempStorage[200];
    char newTempDscStorage[1000];
    char *tempStorage = malloc(sizeof(char) * 1000);
    char *otherTempStorage = malloc(sizeof(char) * 9);
    char tempDateStorage[9];
    char tempTimeStorage[7];
    int count = 0;
    int tempSize = 0;
    int eventFlag = 0;
    int calendarFlag = 0;
    int alarmFlag = 0;
    int versionFlag = 0;
    int proidFlag = 0;
    int uidFlag = 0;
    int dstampFlag = 0;
    int dstartFlag = 0;
    int tempCount = 0;
    int calendarPropCount = 0;
    int eventPropCount = 0;
    int alarmPropCount = 0;
    int totalAlarmCount = 0;
    int totalAlarmPropCount = 0;
    int totalAlarmPropArray[500];
    int totalEventPropArray[500];
    int totalEventAlarmArray[500];
    int totalEventCount = 0;
    int totalEventPropCount = 0;
    int lineStartCount = 0;
    // int firstWrapFlag = 0;
    // int eventAlarmCount = 0;

    //parsing into a string array
    if(fileName != NULL && fileName[0] != '\0')
    {
        // printf("filename is: %s\n", fileName);
        if((strstr(fileName, ".ics")))
        {
            if((fp = fopen(fileName, "r")))
            {
                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    if(line[strlen(line) - 1] == '\n')
                    {
                        line[strlen(line) - 1] = '\0';
                    }

                    if(strlen(line) > 1)
                    {
                        // printf("line strlen is %d\n\n", strlen(line));
                        if(!(isalpha(line[0])) && !(ispunct(line[0])))
                        {
                            memset(newOtherTempStorage, '\0', 1000);
                            // printf("line char[%d] %s\nprevious line: [%d]: %s\n", count, line, count-1, lineStorage[count-1]);
                            // if(firstWrapFlag != 0)
                            // {
                            lineStartCount = strlen(lineStorage[count-1]) - 1;
                            strcpy(newOtherTempStorage, lineStorage[count-1]);

                            //  for(int j = 0; j < strlen(line); j++)
                            // {
                            //     if(!(isalpha(line[j])))
                            //     {
                            //         // j++;
                            //         while(!(isalpha(line[j])))
                            //         {
                            //             if(!(ispunct(line[j])))
                            //             {
                            //                 // newOtherTempStorage[lineStartCount] = line[j];
                            //                 lineStartCount++;
                            //                 j++;
                            //             }
                            //             else
                            //             {
                            //                 break;
                            //             }
                            //         }
                            //     }

                            //     j++;
                            //     while(lineStorage[j] != '\0')
                            //     {
                            //         newOtherTempStorage[lineStartCount] = line[j];
                            //         lineStartCount++;
                            //         j++;
                            //     }
                            // }
                            for(int i = 0; i < strlen(line); i++)
                            {
                                if(!(isalpha(line[i])))
                                {
                                    i++;
                                    while(line[i] != '\0')
                                    {   
                                        newOtherTempStorage[lineStartCount] = line[i];
                                        lineStartCount++;
                                        i++;
                                    }
                                }
                                else if(!ispunct(line[i]))
                                {
                                    i++;
                                    while(line[i] != '\0')
                                    {   
                                        newOtherTempStorage[lineStartCount] = line[i];
                                        lineStartCount++;
                                        i++;
                                    }
                                }
                                // else
                                // {
                                // i++;
                                // }
                            }
                            // // }
                            strcpy(lineStorage[count-1], newOtherTempStorage);
                            lineStartCount = 0;
                        }
                        else
                        {
                            strcpy(lineStorage[count], line);
                            count++;
                            // firstWrapFlag = 0;
                        }
                        // printf("line %s\n", line);
                    }
                }

                fclose(fp);
            }
            else
            {
                // printf("inv1\n");
                return INV_FILE;
            }
        }
        else
        {
            // printf("inv2\n");
            return INV_FILE;
        }
    }
    else
    {
        // printf("inv3\n");
        return INV_FILE;
    }

    Calendar* parseCalendar;
    Alarm * tempAlarm;
    // Property* tempProperty;

    for(int i = 0; i < count; i++)
    {

        // printf("line[%d]: %s\n", i, lineStorage[i]);
        if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 0)
        {
            parseCalendar = initializeCalendar();
            // malloc(sizeof(Calendar));
            // parseCalendar->events = initializeList(NULL, NULL, NULL);
            // parseCalendar->properties = initializeList(NULL, NULL, NULL);
            // (*obj) = malloc(sizeof(Calendar));
            // parseCalendar = initializeCalendar();
            calendarFlag++;
        }
        else if((strcasestr(lineStorage[i], "PRODID")) && calendarFlag == 1 && proidFlag == 0)
        {
            // printf("3\n");

            // if(proidFlag == 0)
            // {
            proidFlag++;
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                // printf("4\n");
                if(lineStorage[i][j] == ':')
                {
                    // printf("5\n");
                    j++;
                    while(lineStorage[i][j+1] != '\0')
                    {
                        // printf("6\n");
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            // printf("prodid: %s\n", tempStorage, linesto);
            if(tempSize != 0)
            {
                strcpy(PROIDStorage, tempStorage);
                strcpy(parseCalendar->prodID, PROIDStorage);
                // printf("prodid: %s\n", parseCalendar->prodID);
            }
            else
            {
                return INV_PRODID;
            }


            tempSize = 0;
            memset(tempStorage, '\0', 1000);
            // }
            // else
            // {
            //     return DUP_PRODID;
            // }
        }
        else if((strcasestr(lineStorage[i], "VERSION")) && calendarFlag == 1)
        {
            // printf("versionflag is %d\n", versionFlag);
            if(versionFlag == 0)
            {
                if((strcasestr(lineStorage[i], "2")))
                {

                    for(int j = 0; j < strlen(lineStorage[i]); j++)
                    {
                        if(lineStorage[i][j] == ':')
                        {
                            j++;
                            while(lineStorage[i][j] != '\0')
                            {
                                tempStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                                j++;
                            }
                        }
                    }


                    strcpy(VersionStorage, tempStorage);
                    tempVersion = atof(VersionStorage);
                    // parseCalendar->version = tempVersion;
                    parseCalendar->version = tempVersion;
                    tempSize = 0;
                    memset(tempStorage, '\0', 1000);
                    versionFlag++;
                }
                else
                {
                    return INV_VER;
                }
            }
            else
            {
                return DUP_VER;
            }
            // printf("versionflagend is %d\n", versionFlag);

        }
        else if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 0 && calendarFlag == 1)
        {
            // printf("9\n");
            eventFlag++;
            totalEventCount++;
            // parseEvent = initializeEvent();

        }
        else if((strcasestr(lineStorage[i], "UID")) && eventFlag == 1)
        {
            // printf("10\n");
            uidFlag++;
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(UIDStorage, tempStorage);
            strcpy(eventUIDStorage[totalEventCount], UIDStorage);
            // printf("eventUID storage is %s\n", eventUIDStorage[totalEventCount]);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((strcasestr(lineStorage[i], "DTSTAMP")) && dstampFlag == 0)
        {
            // printf("11\n");
            dstampFlag++;
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(DSTAMPStorage, tempStorage);
            // char * boolCheck;
            bool tempUTC;
            int tempThirdVal = 0;
            if((strcasestr(DSTAMPStorage, "Z")))
            {
                tempUTC = true;
                strcpy(eventUTCStorage[totalEventCount], "1");
                // parseEvent->creationDateTime.UTC = true;
            }
            else
            {
                tempUTC = false;
                strcpy(eventUTCStorage[totalEventCount], "0");
                // parseEvent->creationDateTime.UTC = false;
            }

            for(int j = 0; j < strlen(DSTAMPStorage); j++)
            {

                while(DSTAMPStorage[j] != 'T')
                {
                    if(DSTAMPStorage[j] != 'T')
                    {
                        tempDateStorage[tempCount] = DSTAMPStorage[j];
                        j++;
                        tempCount++;
                    }
                    else
                    {
                        j++;
                    }
                }

                j++;
                if(tempUTC == true)
                {
                    while(DSTAMPStorage[j+1] != '\0')
                    {

                        if(DSTAMPStorage[j] != 'Z')
                        {
                            tempTimeStorage[tempThirdVal] = DSTAMPStorage[j];
                            j++;
                            tempThirdVal++;
                        }
                        else
                        {
                            j++;
                        }
                    }
                }
                else
                {
                    while(DSTAMPStorage[j+1] != '\0')
                    {
                        tempTimeStorage[tempThirdVal] = DSTAMPStorage[j];
                        j++;
                        tempThirdVal++;
                    }
                }

            }

            // printf("tempDateStorage: %s, tempTimeStorage: %s\n", tempDateStorage, tempTimeStorage);

            if((!strcasestr(DSTAMPStorage, "T")) || tempThirdVal > 7 || tempCount > 9 || tempThirdVal < 5 || tempCount < 7)
            {
                // printf("inv thing 1\n");
                return INV_CREATEDT;
            }
            else
            {
                // printf("tempDateStorage: %s, tempTimeStorage: %s\n", tempDateStorage, tempTimeStorage);
                strcpy(eventDateStorage[totalEventCount], tempDateStorage);
                strcpy(eventTimeStorage[totalEventCount], tempTimeStorage);
                // strcpy(parseEvent->creationDateTime.date, tempDateStorage);
                // strcpy(parseEvent->creationDateTime.time, tempTimeStorage);
            }

            tempSize = 0;
            tempCount = 0;
            tempThirdVal = 0;
            memset(otherTempStorage, '\0', 200);
            memset(tempStorage, '\0', 200); 
        }
        else if((strcasestr(lineStorage[i], "DTSTART")) && dstartFlag == 0)
        {
            // printf("11\n");
            dstartFlag++;
            // printf("dstart0: %s\n", lineStorage[i]);
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(DSTARTStorage, tempStorage);
            // printf("dstart1: %s\n", lineStorage[i]);
            // char * boolCheck;
            bool tempUTC;
            int tempThirdVal = 0;
            if((strcasestr(DSTARTStorage, "Z")))
            {
                tempUTC = true;
                strcpy(eventDSTARTUTCStorage[totalEventCount], "1");
                // parseEvent->creationDateTime.UTC = true;
            }
            else
            {
                tempUTC = false;
                strcpy(eventDSTARTUTCStorage[totalEventCount], "0");
                // parseEvent->creationDateTime.UTC = false;
            }

            for(int j = 0; j < strlen(DSTARTStorage); j++)
            {

                while(DSTARTStorage[j] != 'T')
                {
                    if(DSTARTStorage[j] != 'T')
                    {
                        tempDateStorage[tempCount] = DSTARTStorage[j];
                        j++;
                        tempCount++;
                    }
                    else
                    {
                        j++;
                    }
                }

                j++;
                if(tempUTC == true)
                {
                    while(DSTARTStorage[j+1] != '\0')
                    {

                        if(DSTARTStorage[j] != 'Z')
                        {
                            tempTimeStorage[tempThirdVal] = DSTARTStorage[j];
                            j++;
                            tempThirdVal++;
                        }
                        else
                        {
                            j++;
                        }
                    }
                }
                else
                {
                    while(DSTARTStorage[j+1] != '\0')
                    {
                        tempTimeStorage[tempThirdVal] = DSTARTStorage[j];
                        j++;
                        tempThirdVal++;
                    }
                }

            }

            // printf("dstart2: %s\n", DSTARTStorage);

            // printf("tempDateStorage: %s, tempTimeStorage: %s, tempThirdVal: %d, tempCount: %d\n", tempDateStorage, tempTimeStorage, tempThirdVal, tempCount);

            if((!strcasestr(DSTARTStorage, "T")) || strlen(tempTimeStorage) > 7 || strlen(tempTimeStorage) > 9 || strlen(tempDateStorage) < 5 || strlen(tempDateStorage) < 7)
            {
                // printf("inv thing 2\n");
                return INV_EVENT;
            }
            else
            {
                // printf("tempDateStorage: %s, tempTimeStorage: %s\n", tempDateStorage, tempTimeStorage);
                strcpy(eventDSTARTDateStorage[totalEventCount], tempDateStorage);
                strcpy(eventDSTARTTimeStorage[totalEventCount], tempTimeStorage);
                // strcpy(parseEvent->creationDateTime.date, tempDateStorage);
                // strcpy(parseEvent->creationDateTime.time, tempTimeStorage);
            }

            tempSize = 0;
            tempCount = 0;
            tempThirdVal = 0;
            memset(otherTempStorage, '\0', 200);
            memset(tempStorage, '\0', 200); 
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 1)
        {
            totalEventPropArray[totalEventCount] = totalEventPropCount;
            totalEventAlarmArray[totalEventCount] = totalAlarmCount;
            eventFlag--;
            eventPropCount = 0;
            // printf("dstamp is %d\n", dstampFlag);
            dstampFlag--;
            uidFlag--;
            dstartFlag--;

        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 1)
        {
            Property * testCalInsertVal;
            Event * tempEventInsert;
            Property * tempEventPropInsert;
            Property * propInsert;

            if(calendarPropCount != 0)
            {
                for(int k = 0; k < calendarPropCount; k++)
                {
                    if(strlen(calendarPropDscrStorage[k]) == 0)
                    {
                        // printf("calendar prop name:%s, calendar prop dsc: %s\n", calendarPropNameStorage[k], calendarPropDscrStorage[k]);
                        // printf("lol\n");
                        return INV_CAL;
                    }
                    // printf("calendar prop name:%s, calendar prop dsc: %s\n", calendarPropNameStorage[k], calendarPropDscrStorage[k]);
                    testCalInsertVal = initializeProperty(calendarPropNameStorage[k], calendarPropDscrStorage[k]);
                    insertBack(&parseCalendar->properties, (void*)testCalInsertVal);
                }
            }
            if(totalEventCount > 0)
                // printf("total event count is %d\n", totalEventCount);
                for(int k = 1; k < totalEventCount + 1; k++)
                {
                    // printf("b4 event[%d]: date: %s, time: %s, utc: %s\n", k, eventDateStorage[k], eventTimeStorage[k],eventUTCStorage[k]);
                    // printf("uid should be before insertion: <%s>\n", eventUIDStorage[k]);
                    // char* UID, char* date, char* timeVal, char* UTC)

                    tempEventInsert = initializeEvent(eventDateStorage[k], eventTimeStorage[k], eventUTCStorage[k], eventDSTARTDateStorage[k], eventDSTARTTimeStorage[k], eventDSTARTUTCStorage[k]);
                    strcpy(tempEventInsert->UID, eventUIDStorage[k]);
                    // printf("afterevent[%d]: date: %s, time: %s, utc: %d\n", k, tempEventInsert->creationDateTime.date, tempEventInsert->creationDateTime.time,tempEventInsert->creationDateTime.UTC);
                    // printf("uid after insert is %s\n", tempEventInsert->UID);
                    // printf("k is %d\n", k);

                    if(totalEventPropArray[k] != 0)
                    {
                        if(k == 1)
                        {
                            for(int j = 0; j < totalEventPropArray[k]; j++)
                            {

                                // printf("totalEventPropArray[%d] is %d\n", k, totalEventPropArray[k]);
                                if(strlen(eventPropDscrStorage[j]) == 0)
                                {
                                    // printf("1\n");
                                    return INV_EVENT;
                                }
                                // printf("0prop[%d], event prop name: %s, event prop dscr: %s\n", j,eventPropNameStorage[j], eventPropDscrStorage[j]);
                                tempEventPropInsert = initializeProperty(eventPropNameStorage[j], eventPropDscrStorage[j]);
                                insertBack(&tempEventInsert->properties, (void*)tempEventPropInsert);
                            }
                        }
                        else
                        {
                            // printf("hiya %d\n",k);
                            // printf("12totalEventPropArray[%d] is %d\n", k, totalEventPropArray[k]);
                            for(int j = totalEventPropArray[k - 1]; j < totalEventPropArray[k]; j++)
                            {

                                // printf("j is currently %d\n", j);
                                if(strlen(eventPropDscrStorage[j]) == 0)
                                {
                                    // printf("2\n");
                                    // printf("event[%d], event prop name: %s, event prop dscr: %s\n", k,eventPropNameStorage[j], eventPropDscrStorage[j]);
                                    return INV_EVENT;
                                }
                                // printf("prop[%d], event prop name: %s, event prop dscr: %s\n", j,eventPropNameStorage[j], eventPropDscrStorage[j]);
                                tempEventPropInsert = initializeProperty(eventPropNameStorage[j], eventPropDscrStorage[j]);
                                insertBack(&tempEventInsert->properties, (void*)tempEventPropInsert);
                            }

                        }
                        // printf("k is still %d\n", k);
                    }

                    if(totalEventAlarmArray[k] != 0)
                    {
                        // printf("k is currently %d\n", k);
                        if(k == 1)
                        {
                            // printf("totalalarm1 event array thing at %d is %d\n", k, totalEventAlarmArray[k]);
                            for(int j = 1; j < totalEventAlarmArray[k]+1; j++)
                            {
                                if(strlen(alarmActionStorage[j]) == 0)
                                {
                                    return INV_ALARM;
                                }

                                if(strlen(alarmTriggerStorage[j]) == 0)
                                {
                                    return INV_ALARM;
                                }

                                tempAlarm = initializeAlarm(alarmActionStorage[j], alarmTriggerStorage[j]);
                                if(j == 1)
                                {
                                    for(int m = 0; m < totalAlarmPropArray[j]; m++)
                                    {
                                        // printf("2.1alarm propName: %s, propDescr: %s\n", alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                        propInsert = initializeProperty(alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                        insertBack(&tempAlarm->properties, (void*)propInsert);
                                    }
                                }
                                else
                                {
                                    for(int m = totalAlarmPropArray[j - 1]; m < totalAlarmPropArray[j]; m++)
                                    {
                                        // printf("2alarm propName: %s, propDescr: %s\n", alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                        propInsert = initializeProperty(alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                        insertBack(&tempAlarm->properties, (void*)propInsert);
                                    }
                                }
                                insertBack(&tempEventInsert->alarms, tempAlarm);
                                // printf("action: %s, trigger: %s\n", alarmActionStorage[j], alarmTriggerStorage[j]);
                            }
                        }
                        else
                        {
                            // printf("totalalarm event array thing at %d is %d\n", k, totalEventAlarmArray[k] + 1);
                            for(int j = totalEventAlarmArray[k - 1]; j < totalEventAlarmArray[k]; j++)
                            {

                                if(strlen(alarmActionStorage[j]) == 0)
                                {
                                    return INV_ALARM;
                                }

                                if(strlen(alarmTriggerStorage[j]) == 0)
                                {
                                    return INV_ALARM;
                                }
                                tempAlarm = initializeAlarm(alarmActionStorage[j], alarmTriggerStorage[j]);
                                // printf("j is %d\n", j);
                                for(int m = totalAlarmPropArray[j - 1]; m < totalAlarmPropArray[j]; m++)
                                {
                                    // printf("m val is %d\n", m);
                                    // printf("3alarm propName: %s, propDescr: %s\n", alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                    propInsert = initializeProperty(alarmPropNameStorage[m], alarmPropDscrStorage[m]);
                                    insertBack(&tempAlarm->properties, (void*)propInsert);
                                }
                                insertBack(&tempEventInsert->alarms, tempAlarm);
                                // printf("3action: %s, trigger: %s\n", alarmActionStorage[j], alarmTriggerStorage[j]);
                                // printf("int j = %d\n", j);

                            }
                        }

                    }
                    // printf("inserting event\n");
                    insertBack(&parseCalendar->events, tempEventInsert);
                }

            calendarFlag++;
        }
        else if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VALARM")) && eventFlag == 1 && alarmFlag == 0)
        {
            alarmFlag++;
            totalAlarmCount++;
        }
        else if((strcasestr(lineStorage[i], "TRIGGER")) && calendarFlag == 1 &&  eventFlag == 1 && alarmFlag == 1)
        {
            memset(newOtherTempStorage, '\0', 256);
            memset(triggerStorage, '\0', 256); 
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ';')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        newOtherTempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
                else if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        newOtherTempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
            }

            // printf("tempstorage trigger is %s size is %d\n", newOtherTempStorage, tempSize);
            if(newOtherTempStorage[0] == '\0' && alarmTriggerStorage[totalAlarmCount] != NULL)
            {
                // printf("5\n");
                return INV_EVENT;

                // printf("tempsize isnt 0\n");
            }

            strcpy(alarmTriggerStorage[totalAlarmCount], newOtherTempStorage);
            tempSize = 0;
            memset(newOtherTempStorage, '\0', 256);
            memset(triggerStorage, '\0', 256); 
        }
        else if((strcasestr(lineStorage[i], "ACTION")) && calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
        {
            // printf("fuck\n");
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j+1] != '\0')
                    {
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
            }


            if(tempStorage[0] == '\0')
            {
                // printf("6\n");
                return INV_EVENT;
            }
            // tempStorage[tempSize - 1] = '\0';
            // strcpy(actionStorage, tempStorage);
            strcpy(alarmActionStorage[totalAlarmCount], tempStorage);
            // if(actionStorage == NULL)
            // {
            //     return INV_EVENT;
            // }
            // printf("action storage is %s, tempsize is %d\n", actionStorage, tempSize);
            // strcpy(tempAlarm->action, actionStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
            memset(actionStorage,'\0', 200);
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VALARM")) && calendarFlag == 1 && alarmFlag == 1 && eventFlag == 1)
        {
            totalAlarmPropArray[totalAlarmCount] = totalAlarmPropCount;

            memset(triggerStorage, '\0', 200);
            memset(actionStorage,'\0', 200);
            // printf("6b\n");
            alarmFlag--;
            alarmPropCount = 0;
            // printf("6d\n");
        }
        else if((strcasestr(lineStorage[i], "VERSION")) && versionFlag == 1)
        {
            // printf("hullo this shis is a dupe\n");
            return DUP_VER;
        }
        else if((strcasestr(lineStorage[i], "PRODID")) && proidFlag == 1)
        {
            return DUP_PRODID;
        }
        else if(((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag >= 1 && calendarFlag == 1))
        {
            return INV_EVENT;
        }
        else if(((strcasestr(lineStorage[i], "BEGIN"))) && !(strcasestr(lineStorage[i],"VEVENT")) && !(strcasestr(lineStorage[i],"VCALENDAR")) && !(strcasestr(lineStorage[i],"VALARM")))
        {
            // if(!(strcasestr(lineStorage[i],"VEVENT")) && !(strcasestr(lineStorage[i],"VCALENDAR")) && !(strcasestr(lineStorage[i],"VALARM")))
            // {
            // printf("2lol at line[%d]: %s\n", i, lineStorage[i]);
            return INV_CAL;
            // }
        }
        else if(((strcasestr(lineStorage[i], "SUMMARY")) &&  eventFlag == 0 && calendarFlag == 1))
        {
            // printf("moop\n");
            // printf("3\n");
            return INV_CAL;
        }
        //alarm property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1 && lineStorage[i][0] != ';')
        {
            // printf("test prop fucker\n");
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] != ':')
                {
                    // j++;
                    while(lineStorage[i][j] != ':')
                    {
                        if(lineStorage[i][j] != ';')
                        {
                            newTempStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                j++;
                while(lineStorage[i][j+1] != '\0')
                {
                    newTempDscStorage[tempCount] = lineStorage[i][j];
                    tempCount++;
                    j++;
                }
            }

            if(tempSize != 0 && tempCount != 0)
            {
                // if(newTempStorage[tempSize - 1] == '\n')
                // {
                //         newTempStorage[tempSize - 1] = '\0';
                // }

                // if(newTempDscStorage[tempCount - 1] == '\n')
                // {
                newTempDscStorage[tempCount+1] = '\0';
                // }

                strcpy(alarmPropNameStorage[totalAlarmPropCount], newTempStorage);
                strcpy(alarmPropDscrStorage[totalAlarmPropCount], newTempDscStorage);
                alarmPropCount++;
                totalAlarmPropCount++;


            }  
            else
            {
                // printf("6\n");
                return INV_EVENT;
            } 

            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 200);
            memset(newTempDscStorage, '\0', 1000);
        }
        //event property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 0 && lineStorage[i][0] != ';')
        {

            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] != ':')
                {
                    // j++;
                    while(lineStorage[i][j] != ':')
                    {
                        if(lineStorage[i][j] != ';')
                        {
                            newTempStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                        }
                        // else if(lineStorage[i][j] == ';')
                        // {
                        //     return INV_EVENT;
                        // }
                        else
                        {
                            break;
                        }
                    }
                }

                j++;
                while(lineStorage[i][j+1] != '\0')
                {
                    newTempDscStorage[tempCount] = lineStorage[i][j];
                    tempCount++;
                    j++;
                }
            }

            // if()
            //   for(int k = 0; k < eventPropCount; k++)
            // {
            //     if(strcmp(eventPropNCount[k], newTempStorage) == 0)
            //     {
            //         return INV_EVENT;
            //     }
            // }

            // printf("nLine|%c|\n", lineStorage[i+1][0]);
            // if(strcasestr(lineStorage[i],"DTSTART"))
            // {
            //     if(!(strcasestr(lineStorage[i+1], "DURATION")))
            //     {
            //         if(strcasestr(lineStorage[i+1], "DTEND"))
            //         {
            //             if(strcasestr(lineStorage[i+2], "DURATION"))
            //             {
            //                 return INV_EVENT;
            //             }
            //         }
            //     }
            //     else
            //     {
            //         if(!(strcasestr(lineStorage[i+2], "DTEND")))
            //         {
            //             return INV_EVENT;
            //         }
            //     }
            // }

            if(strcasestr(lineStorage[i], "DURATION"))
            {
                if((strcasestr(lineStorage[i-1], "DTSTART")))
                {
                    if(!(strcasestr(lineStorage[i+1], "DTEND")))
                    {
                        return INV_EVENT;
                    }
                }
                else
                {
                    return INV_EVENT;   
                }
            }



            if(tempSize != 0 && tempCount != 0)
            {
                // if(newTempStorage[tempSize - 1] == '\n')
                // {
                //         newTempStorage[tempSize - 1] = '\0';
                // }

                // if(newTempDscStorage[tempCount - 1] == '\n')
                // {
                // newTempDscStorage[tempCount - 1] = '\0';
                // }

                // printf("prop dscr is now <%s>\n", newTempDscStorage);

                if(strlen(newTempDscStorage) != 0)
                {



                    strcpy(eventPropNameStorage[totalEventPropCount], newTempStorage);
                    strcpy(eventPropDscrStorage[totalEventPropCount], newTempDscStorage);
                    eventPropCount++;
                    totalEventPropCount++;

                }
                else
                {
                    return INV_EVENT;
                }
            }  
            else
            {
                // printf("7\n");
                return INV_EVENT;
            } 
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 200);
            memset(newTempDscStorage, '\0', 1000);
            // memset(finalTempStorage, '\0', 256);
        }

        //calendar property
        else if(calendarFlag == 1 && eventFlag == 0 && alarmFlag == 0 && lineStorage[i][0] != ';')
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] != ':')
                {
                    // j++;
                    while(lineStorage[i][j] != ':')
                    {
                        if(lineStorage[i][j] != ';')
                        {
                            newTempStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                j++;
                while(lineStorage[i][j+1] != '\0')
                {
                    newTempDscStorage[tempCount] = lineStorage[i][j];
                    tempCount++;
                    j++;
                }
            }

            for(int k = 0; k < calendarPropCount; k++)
            {
                if(strcmp(calendarPropNameStorage[k], newTempStorage) == 0)
                {
                    // printf("4\n");
                    return INV_CAL;
                }
            }




            if(tempSize != 0 && tempCount != 0)
            {
                // if(newTempStorage[tempSize - 1] == '\n')
                // {
                //         newTempStorage[tempSize - 1] = '\0';
                // }

                // if(newTempDscStorage[tempCount - 1] == '\n')
                // {
                // newTempDscStorage[tempCount - 1] = '\0';
                // }

                // printf("prop dscr is now <%s>\n", newTempDscStorage);

                strcpy(calendarPropNameStorage[calendarPropCount], newTempStorage);
                strcpy(calendarPropDscrStorage[calendarPropCount], newTempDscStorage);
                calendarPropCount++;
                // totalEventPropCount++;


            }  
            else
            {
                // printf("8\n");
                return INV_EVENT;
            } 
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 200);
            memset(newTempDscStorage, '\0', 1000);
        }
        // else if((strcasestr(lineStorage[i], "VERSION")) && versionFlag == 1)

    }
    // printf("hi\n");
    // printf("\n\nfucker\ncalendarflag: %d, proidFlag: %d, versionFlag: %d, eventFlag:%d\n\n", calendarFlag, proidFlag, versionFlag, eventFlag);
    if(calendarFlag != 2 || proidFlag != 1 || versionFlag != 1 || eventFlag != 0)
    {
        // printf("5\n");
        // printf("\n\ninter\ncalendarflag: %d, proidFlag: %d, versionFlag: %d, eventFlag:%d\n\n", calendarFlag, proidFlag, versionFlag, eventFlag);
        return INV_CAL;
    }
    else if(uidFlag != 0 || dstampFlag != 0)
    {
        // printf("p00py\n");
        // printf("uid flag is at %d, dstamp flag is at %d\n", uidFlag, dstampFlag);
        return INV_EVENT;
    }
    else
    {
        if(calendarFlag == 1)
        {
            // printf("6\n");
            return INV_CAL;
        }
        // printf("version flag is %d at the end\n\n", versionFlag);
        if(parseCalendar->events.head == NULL)
        {
            return INV_EVENT;
        }
        // printf("what\n");
        *obj = parseCalendar;
        return OK;
    }

}

ICalErrorCode writeCalendar(char* fileName, const Calendar* obj)
{

    FILE *fo;
    // printf("butthole\n");
    if(fileName != NULL && fileName[0] != '\0')
    {
        // printf("filename is: %s\n", fileName);
        if((strstr(fileName, ".ics")))
        {
            // printf("hi\n");

            // printf("1\n");
            if((fo = fopen(fileName, "w")))
            {
                // printf("hoe\n");
                char * calendarWrite = malloc(sizeof(char) * 1000);
                // printf("2\n");
                sprintf(calendarWrite + strlen(calendarWrite), "BEGIN:VCALENDAR \nVERSION:%.1f \nPRODID:%s \n", (*obj).version, (*obj).prodID);
                // printf("3\n");
                if(obj->properties.length > 0)
                {
                    void *calPropWriteElem;
                    ListIterator tempCalPropWriteIter = createIterator(obj->properties);
                    // printf("4\n");
                    while((calPropWriteElem = nextElement(&tempCalPropWriteIter)) != NULL)
                    {
                        Property* tempCalPropWrite = (Property*)calPropWriteElem;
                        sprintf(calendarWrite + strlen(calendarWrite), "%s:%s \n", tempCalPropWrite->propName, tempCalPropWrite->propDescr);
                    }
                    // printf("5\n");
                }
                // printf("5.5\n");
                void *calEventWriteElem;
                // printf("5.6\n");
                ListIterator tempCalEventWriteIter = createIterator(obj->events);
                // printf("5.7\n");
                // printf("#of events is %d\n", obj->events.length);
                while((calEventWriteElem = nextElement(&tempCalEventWriteIter)) != NULL)
                {
                    // printf("6\n");
                    Event* tempCalEventWrite = (Event*)calEventWriteElem;
                    sprintf(calendarWrite + strlen(calendarWrite), "BEGIN:VEVENT \nUID:%s \n", tempCalEventWrite->UID);

                    if(strlen(tempCalEventWrite->creationDateTime.date) != 0)
                    {
                        if(tempCalEventWrite->creationDateTime.UTC == 1)
                        {
                            sprintf(calendarWrite + strlen(calendarWrite), "DTSTAMP:%sT%sZ \n", tempCalEventWrite->creationDateTime.date, tempCalEventWrite->creationDateTime.time);
                        }
                        else
                        {
                            sprintf(calendarWrite + strlen(calendarWrite), "DTSTAMP:%sT%s \n", tempCalEventWrite->creationDateTime.date, tempCalEventWrite->creationDateTime.time);
                        }
                    }

                    // printf("7\n");
                    if(strlen(tempCalEventWrite->startDateTime.date) != 0)
                    {


                        if(tempCalEventWrite->startDateTime.UTC == 1)
                        {
                            sprintf(calendarWrite + strlen(calendarWrite), "DTSTART:%sT%sZ \n", tempCalEventWrite->startDateTime.date, tempCalEventWrite->startDateTime.time);
                        }
                        else
                        {
                            sprintf(calendarWrite + strlen(calendarWrite), "DTSTART:%sT%s \n", tempCalEventWrite->startDateTime.date, tempCalEventWrite->startDateTime.time);
                        }


                    }
                    // printf("8\n");
                    if(tempCalEventWrite->properties.length > 0)
                    {


                        void *calEventPropWriteElem;
                        ListIterator tempCalEventPropWriteIter = createIterator(tempCalEventWrite->properties);
                        while((calEventPropWriteElem = nextElement(&tempCalEventPropWriteIter)) != NULL)
                        {
                            Property* tempCalEventPropWrite = (Property*)calEventPropWriteElem;
                            sprintf(calendarWrite + strlen(calendarWrite), "%s:%s \n", tempCalEventPropWrite->propName, tempCalEventPropWrite->propDescr);
                        }
                    }
                    // printf("9\n");

                    if(tempCalEventWrite->alarms.length > 0)
                    {
                        void *calEventAlarmWriteElem;
                        ListIterator tempCalEventAlarmWriteIter = createIterator(tempCalEventWrite->alarms);
                        while((calEventAlarmWriteElem = nextElement(&tempCalEventAlarmWriteIter)) != NULL)
                        {
                            Alarm* tempCalEventAlarmWrite = (Alarm*)calEventAlarmWriteElem;
                            sprintf(calendarWrite + strlen(calendarWrite), "BEGIN:VALARM \nACTION:%s \nTRIGGER:%s \n", tempCalEventAlarmWrite->action, tempCalEventAlarmWrite->trigger);
                            void *calEventAlarmPropWriteElem;
                            ListIterator tempCalEventAlarmPropWriteIter = createIterator(tempCalEventAlarmWrite->properties);
                            while((calEventAlarmPropWriteElem = nextElement(&tempCalEventAlarmPropWriteIter)) != NULL)
                            {
                                Property* tempCalEventAlarmPropWrite = (Property*)calEventAlarmPropWriteElem;
                                sprintf(calendarWrite + strlen(calendarWrite), "%s:%s \n", tempCalEventAlarmPropWrite->propName, tempCalEventAlarmPropWrite->propDescr);
                            }
                            sprintf(calendarWrite + strlen(calendarWrite), "END:VALARM \n");

                        }
                    }
                    // printf("10\n");
                    sprintf(calendarWrite + strlen(calendarWrite), "END:VEVENT \n");
                }
                // printf("11\n");
                sprintf(calendarWrite + strlen(calendarWrite), "END:VCALENDAR \n");

                // printf("is this shit on\n");
                fputs(calendarWrite, fo);
                fclose(fo);
                return OK;
                // fclose(fo);
            }
            else
            {
                // printf("somethings fucky\n");
                return WRITE_ERROR;
            }
        }
        else
        {
            // printf("nah you fucky\n");
            return WRITE_ERROR;
        }
    }
    else
    {
        // printf("hella fucky\n");
        return WRITE_ERROR;
    }
    return OK;


}

ICalErrorCode validateCalendar(const Calendar* obj)
{

    /*  go through each line of the calendar and make sure its not fucked like in writecalendar
        otherwise return the proper error code. */
    if(obj != NULL)
    {
        // char * str = printCalendar(obj);
        // printf("err cal is %s\n", str);
        if(strlen((obj)->prodID) == 0)
        {
            return INV_PRODID;
        }

        if((obj)->version != 2)
        {
            return INV_VER;
        }

        if((obj)->events.length == 0)
        {
            return INV_CAL;
        }
        else
        {
            void *calEventsElem;
            ListIterator calEventsElemIter = createIterator(obj->events);
            // int prodIDDupeFlag = 0;
            while((calEventsElem = nextElement(&calEventsElemIter)) != NULL)
            {
                Event* tempCalEventCheck = (Event*)calEventsElem;
                // if(tempCalEventCheck->creationDateTime.UTC != 1 || tempCalEventCheck->creationDateTime.UTC != 0)
                // {
                //     return INV_CREATEDT;
                // }

                if(strlen(tempCalEventCheck->creationDateTime.time) == 0)
                {
                    printf("inv thing 3\n");
                    return INV_CREATEDT;
                }

                if(strlen(tempCalEventCheck->creationDateTime.date) == 0)
                {
                    // printf("inv thing 4\n");
                    return INV_CREATEDT;
                }

                if(strlen(tempCalEventCheck->UID) == 0)
                {
                    printf("inv evnet 1\n");
                    printf("UID: %s\n", tempCalEventCheck->UID);
                    return DUP_PRODID;
                }
                // else
                // {
                // if(prodIDDupeFlag == 0)
                // {
                //    prodIDDupeFlag++; 
                // }
                // else
                // {
                //     return DUP_PRODID;
                // }

                // }

                if(tempCalEventCheck->properties.length > 0)
                {
                    int lengthCheck = 0;
                    void *eventPropElem;
                    ListIterator eventPropElemIter = createIterator(tempCalEventCheck->properties);
                    while((eventPropElem = nextElement(&eventPropElemIter)) != NULL)
                    {
                        Property* tempEventPropCheck = (Property*)eventPropElem;
                        if(strcasestr(tempEventPropCheck->propName, "PRODID"))
                        {
                            return DUP_PRODID;
                        }

                        if(strlen(tempEventPropCheck->propName) == 0)
                        {
                            printf("e1\n");
                            return INV_EVENT;
                        }

                        if(strlen(tempEventPropCheck->propDescr) == 0)
                        {
                            printf("e2\n");
                            return INV_EVENT;
                        }
                        // lengthCheck++;
                        int dupeLengthCheck = 0;
                        void * eventPropDupeElem;
                        ListIterator eventPropDupeElemIter = createIterator(tempCalEventCheck->properties);
                        while((eventPropDupeElem = nextElement(&eventPropDupeElemIter)) != NULL)
                        {
                            Property* eventPropDupeCheck = (Property*)eventPropDupeElem;
                            // printf("og name: %s, dupecheck name: %s\nog dscr: %s, dupecheck dscr: %s\n", tempEventPropCheck->propName, eventPropDupeCheck->propName, tempEventPropCheck->propDescr, eventPropDupeCheck->propDescr);
                            if(dupeLengthCheck != lengthCheck)
                            {

                                // printf("duplength is %d, length is %d\n", dupeLengthCheck, lengthCheck);
                                // printf("og name: %s, dupecheck name: %s\nog dscr: %s, dupecheck dscr: %s\n", tempEventPropCheck->propName, eventPropDupeCheck->propName, tempEventPropCheck->propDescr, eventPropDupeCheck->propDescr);
                                if(strcasestr(eventPropDupeCheck->propName, "PRODID"))
                                {
                                    return DUP_PRODID;
                                }

                                if(strcmp(tempEventPropCheck->propName, eventPropDupeCheck->propName) == 0)
                                {
                                    // printf("e3\n");
                                    // printf("og name: %s, dupecheck name: %s\nog dscr: %s, dupecheck dscr: %s\n", tempEventPropCheck->propName, eventPropDupeCheck->propName, tempEventPropCheck->propDescr, eventPropDupeCheck->propDescr);
                                    return INV_EVENT;
                                }

                                if(strcmp(tempEventPropCheck->propDescr, eventPropDupeCheck->propDescr) == 0)
                                {
                                    // printf("e4\n");
                                    return INV_EVENT;
                                }

                                if(strcasestr(eventPropDupeCheck->propName, "Duration"))
                                {
                                    // printf("e5\n");
                                    return INV_EVENT;
                                }

                                // if(strcasestr(eventPropDupeCheck->propName, "PRODID"))
                                // {
                                //     return DUP_PRODID;
                                // }
                            }
                            dupeLengthCheck++;
                        }
                        lengthCheck++;

                    }
                }

                if(tempCalEventCheck->alarms.length != 0)
                {
                    // int lengthCheck = 0;
                    void *eventAlarmElem;
                    ListIterator eventAlarmElemIter = createIterator(tempCalEventCheck->alarms);
                    while((eventAlarmElem = nextElement(&eventAlarmElemIter)) != NULL)
                    {
                        Alarm* tempEventAlarmCheck = (Alarm*)eventAlarmElem;
                        if(strlen(tempEventAlarmCheck->action) == 0)
                        {
                            return INV_ALARM;
                        }
                        if(strlen(tempEventAlarmCheck->trigger) == 0)
                        {
                            return INV_ALARM;
                        }

                        if(tempEventAlarmCheck->properties.length != 0)
                        {
                            int lengthCheck = 0;
                            void *alarmPropElem;
                            ListIterator alarmPropElemIter = createIterator(tempEventAlarmCheck->properties);
                            while((alarmPropElem = nextElement(&alarmPropElemIter)) != NULL)
                            {
                                Property* tempAlarmPropCheck = (Property*)alarmPropElem;
                                if(strlen(tempAlarmPropCheck->propName) == 0)
                                {
                                    return INV_ALARM;
                                }
                                if(strlen(tempAlarmPropCheck->propDescr) == 0)
                                {
                                    return INV_ALARM;
                                }

                                int dupeLengthCheck = 0;
                                void * alarmPropDupeElem;
                                ListIterator alarmPropDupeElemIter = createIterator(tempEventAlarmCheck->properties);
                                while((alarmPropDupeElem = nextElement(&alarmPropDupeElemIter)) != NULL)
                                {
                                    Property* alarmPropDupeCheck = (Property*)alarmPropDupeElem;
                                    if(dupeLengthCheck != lengthCheck)
                                    {
                                        if(strcmp(tempAlarmPropCheck->propName, alarmPropDupeCheck->propName) == 0)
                                        {
                                            return INV_ALARM;
                                        }

                                        if(strcmp(tempAlarmPropCheck->propDescr, alarmPropDupeCheck->propDescr) == 0)
                                        {
                                            return INV_ALARM;
                                        }
                                    }
                                    dupeLengthCheck++;
                                }
                                lengthCheck++;
                            }
                        }
                    }
                }
            }
        }

        if((obj)->properties.length != 0)
        {
            int lengthCheck = 0;
            void *calPropElem;
            ListIterator calPropElemIter = createIterator(obj->properties);
            while((calPropElem = nextElement(&calPropElemIter)) != NULL)
            {
                Property* tempCalPropCheck = (Property*)calPropElem;
                if(strlen(tempCalPropCheck->propName) == 0)
                {
                    return INV_CAL;
                }

                if(strlen(tempCalPropCheck->propDescr) == 0)
                {
                    return INV_CAL;
                }

                int dupeLengthCheck = 0;
                void * calPropDupeElem;
                ListIterator calPropDupeElemIter = createIterator(obj->properties);
                while((calPropDupeElem = nextElement(&calPropDupeElemIter)) != NULL)
                {
                    Property* calPropDupeCheck = (Property*)calPropDupeElem;
                    if(dupeLengthCheck != lengthCheck)
                    {
                        // printf("duplength is %d, length is %d\n", dupeLengthCheck, lengthCheck);
                        if(strcmp(tempCalPropCheck->propName, calPropDupeCheck->propName) == 0)
                        {
                            // printf("e3\n");
                            return INV_CAL;
                        }

                        if(strcmp(tempCalPropCheck->propDescr, calPropDupeCheck->propDescr) == 0)
                        {
                            // printf("e4\n");
                            return INV_CAL;
                        }

                        // if(strcasestr(calPropDupeCheck->propName, "PRODID"))
                        // {
                        //     return DUP_PRODID;
                        // }
                    }
                    dupeLengthCheck++;
                }
                lengthCheck++;
            }
        }

        return OK;
    }
    else
    {
        return INV_CAL;
    }
}

void deleteCalendar(Calendar* obj)
{
    // printf("f000k\n\n\n");
    if(obj != NULL)
    {
        void *calPropDeleteElem;
        void *eventDeleteElem;
        ListIterator calPropDeleteIter = createIterator(obj->properties);
        while((calPropDeleteElem = nextElement(&calPropDeleteIter)) != NULL)
        {
            List* tempCalPropDelete = (List*)calPropDeleteElem;
            clearList(tempCalPropDelete);
        }

        ListIterator eventDeleteIter = createIterator(obj->events);
        while((eventDeleteElem = nextElement(&eventDeleteIter)) != NULL)
        {
            Event* tempEventDelete = (Event*)eventDeleteElem;

            void *eventAlarmsDeleteElem;
            ListIterator eventAlarmsDeleteIter = createIterator(tempEventDelete->alarms);
            while((eventAlarmsDeleteElem = nextElement(&eventAlarmsDeleteIter)) != NULL)
            {
                Alarm* tempEventAlarmDelete = (Alarm*)eventAlarmsDeleteElem;
                // clearList(tempEventAlarmDelete);
                void *alarmPropDeleteElem;
                ListIterator alarmPropDeleteIter = createIterator(tempEventAlarmDelete->properties);
                while((alarmPropDeleteElem = nextElement(&alarmPropDeleteIter)) != NULL)
                {
                    List* tempAlarmPropDelete = (List*)alarmPropDeleteElem; 
                    clearList(tempAlarmPropDelete);
                }
            }

            void *eventPropertiesDeleteElem;
            ListIterator eventPropertiesDeleteIter = createIterator(tempEventDelete->properties);
            while((eventPropertiesDeleteElem = nextElement(&eventPropertiesDeleteIter)) != NULL)
            {
                List* tempEventPropertiesDelete = (List*)eventPropertiesDeleteElem;
                clearList(tempEventPropertiesDelete);
            }
        }

        // free(obj->events);
        free(obj);
    }
}

char* printCalendar(const Calendar* obj)
{

    char * calendarReturn = malloc(sizeof(char) * 1000);

    if(obj != NULL)
    {
        sprintf(calendarReturn, "\n\nCalendar\n     Version = %f, ProdID = %s\n", obj->version, obj->prodID);

        if(obj->events.head != NULL)
        {
            void* eventElem;
            ListIterator eventIter = createIterator(obj->events);
            while((eventElem = nextElement(&eventIter)) != NULL)
            {

                Event* tempEventPrint = (Event*)eventElem;

                sprintf(calendarReturn + strlen(calendarReturn), "\nEvent\nUID = %s\n", tempEventPrint->UID);
                // if(obj->event->creationDateTime.date != NULL)
                // {
                sprintf(calendarReturn + strlen(calendarReturn), "  creationDateTime = %s:%s UTC = %d\n", tempEventPrint->creationDateTime.date, tempEventPrint->creationDateTime.time, tempEventPrint->creationDateTime.UTC);
                // }

                if(tempEventPrint->alarms.head != NULL)
                {
                    strcat(calendarReturn, "\nAlarms:\n");
                    void* elem;
                    ListIterator eventAlarmsIter = createIterator(tempEventPrint->alarms);
                    while((elem = nextElement(&eventAlarmsIter)) != NULL)
                    {
                        Alarm* tempAlarmPrint = (Alarm*)elem;

                        sprintf(calendarReturn + strlen(calendarReturn), "  Action: %s\n    Trigger: %s\n   Properties:\n",tempAlarmPrint->action, tempAlarmPrint->trigger);
                        ListIterator eventAlarmsPropIter = createIterator(tempAlarmPrint->properties);
                        void *propElem;
                        while((propElem = nextElement(&eventAlarmsPropIter)) != NULL)
                        {
                            Property* tempPropPrint = (Property*)propElem;
                            sprintf(calendarReturn + strlen(calendarReturn), "      %s:%s\n", tempPropPrint->propName, tempPropPrint->propDescr);
                        }

                    }
                }

                strcat(calendarReturn + strlen(calendarReturn), "\nOther Properties:\n");

                void *eventPropElem;
                ListIterator eventPropertiesIter = createIterator(tempEventPrint->properties);
                while((eventPropElem = nextElement(&eventPropertiesIter)) != NULL)
                {
                    Property* tempEventPropPrint = (Property*)eventPropElem;
                    sprintf(calendarReturn + strlen(calendarReturn), "  %s:%s\n", tempEventPropPrint->propName, tempEventPropPrint->propDescr);
                }
            }
        }

        return calendarReturn;
    }

    return NULL;

}

char* printError(ICalErrorCode err)
{

    // printf("%U is entered\n", err);
    char * errorCodeReturn = malloc(sizeof(char) * 256);
    if(err == INV_FILE)
    {
        strcpy(errorCodeReturn, "INV_FILE: there’s a problem with file argument - its null, it;’s a empty string, file doesn't exist or - cannot be opened,file doesn't have the.ics extension\n");
    }
    else if(err == INV_VER)
    {

        strcpy(errorCodeReturn, "INV_VER: the calendar version property is present but malformed\n");
    }
    else if(err == DUP_VER)
    {

        strcpy(errorCodeReturn,"DUP_VER: the calendar version property appears more than once\n");
    }
    else if(err == INV_PRODID)
    {

        strcpy(errorCodeReturn, "INV_PRODID: the product ID property is present but malformed\n");
    }
    else if(err == DUP_PRODID)
    {

        strcpy(errorCodeReturn, "DUP_PRODID: the product ID property appears more than once\n");
    }
    else if(err == INV_CAL)
    {

        strcpy(errorCodeReturn, "INV_CAL: the calendar itself is invalid (missing required properties or components, invalid opening - closingtags,etc.)\n");
    }
    else if(err == INV_CREATEDT)
    {

        strcpy(errorCodeReturn, "INV_CREADEDT: the event creation date-time property is malformed in some way\n");
    }
    else if(err == INV_EVENT)
    {

        strcpy(errorCodeReturn, "INV_EVENT: the event component is malformed in some way\n");
    }
    else if(err == INV_ALARM)
    {
        strcpy(errorCodeReturn, "INV_ALARM: the alarm component is malformed in some way\n");
    }
    else if(err == WRITE_ERROR)
    {
        strcpy(errorCodeReturn, "WRITE_ERROR: Error writing to calendar\n");
    }
    else if (err == OTHER_ERROR)
    {
        strcpy(errorCodeReturn, "OTHER_ERROR: Some other error has happened\n");
    }
    else if(err == OK)
    {
        strcpy(errorCodeReturn, "OK: File parsed successfully.\n");
    }
    else
    {
        strcpy(errorCodeReturn, "error code not found\n");
    }

    return errorCodeReturn;

}

// char* grabOrgName()
// {

// }
char* printSummary(const Calendar* eventPointer)
{
    void *eventPropElem;
    ListIterator eventPropertiesIter = createIterator(eventPointer->properties);
    while((eventPropElem = nextElement(&eventPropertiesIter)) != NULL)
    {
        Property* tempEventPropPrint = (Property*)eventPropElem;
        if(strcasestr(tempEventPropPrint->propName, "SUMMARY"))
        {
            return tempEventPropPrint->propDescr;
        }
    }
    return NULL;
}


Calendar* initializeCalendar()
{
    Calendar * parseCalendar = malloc(sizeof(Calendar));
    parseCalendar->events = initializeList(NULL, NULL, NULL);
    parseCalendar->properties = initializeList(NULL, NULL, NULL);

    return parseCalendar;
}

void manualCalInit(Calendar** obj, char* PRODID)
{
    *obj = initializeCalendar();
    (*obj)->version = 2.0;
    strcpy((*obj)->prodID, PRODID);
    // printf("#of events is %d\n", (*obj)->events.length);
}

void manualEventInit(Calendar** obj, char* uid, char* date, char* timeVal)
{
    Event * tempEvent = malloc(sizeof(Event));
    tempEvent->properties = initializeList(NULL, NULL, NULL);
    tempEvent->alarms = initializeList(NULL, NULL, NULL);


    // printf("uid: %s, date: %s, time:%s\n", uid, date, timeVal);
    strcpy(tempEvent->creationDateTime.date, date);
    strcpy(tempEvent->creationDateTime.time, timeVal);
    tempEvent->creationDateTime.UTC = false;

    strcpy(tempEvent->startDateTime.date, date);
    strcpy(tempEvent->startDateTime.time, timeVal);
    tempEvent->startDateTime.UTC = false;

    insertBack(&(*obj)->events, tempEvent);

    // printf("#of events is %d\n", (*obj)->events.length);
}

int getEventListSize(const Calendar* obj)
{
    return obj->events.length;
}

int getPropertyListSize(const Calendar* obj)
{
    return obj->properties.length;
}





Event* initializeEvent(char* date, char* timeVal, char* UTC, char* dateTwo, char* timeValTwo, char* UTCTwo)
{

    Event * tempEvent = malloc(sizeof(Event));
    tempEvent->properties = initializeList(NULL, NULL, NULL);
    tempEvent->alarms = initializeList(NULL, NULL, NULL);

    // strcpy(tempEvent->UID, UID);
    strcpy(tempEvent->creationDateTime.date, date);
    strcpy(tempEvent->creationDateTime.time, timeVal);
    if(UTC[0] == '1')
    {
        tempEvent->creationDateTime.UTC = true;
    }
    else
    {
        tempEvent->creationDateTime.UTC = false;
    }

    strcpy(tempEvent->startDateTime.date, dateTwo);
    strcpy(tempEvent->startDateTime.time, timeValTwo);
    if(UTCTwo[0] == '1')
    {
        tempEvent->startDateTime.UTC = true;
    }
    else
    {
        tempEvent->startDateTime.UTC = false;
    }

    return tempEvent;
}

Property* initializeProperty(char* propName, char* propDescr)
{

    Property* tempProp;

    tempProp = malloc(sizeof(Property) + (sizeof(char)*(strlen(propDescr)+1)));
    strcpy(tempProp->propName, propName);
    strcpy(tempProp->propDescr, propDescr);
    // printf("name: %s, dsc: %s\n", tempProp->propName, tempProp->propDescr);

    return tempProp;

}

Alarm* initializeAlarm(char* action, char* trigger)
{

    Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->trigger = malloc(sizeof(char) * (strlen(trigger)+1));
    tempAlarm->properties = initializeList(NULL, NULL, NULL);

    strcpy(tempAlarm->trigger, trigger);
    strcpy(tempAlarm->action, action);

    return tempAlarm;

}

void  tDestroy(void *data)
{
    free(data);
}

char * tPrint(void *toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

int tCompare(const void * one, const void * two)
{
    return strcmp((char*)one, (char*)two);
}


