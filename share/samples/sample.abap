*
* This program interprets the sequential file created by ZHEAVYPR
* and displays the "heavy" ABAPs of a specified period of time.
* The result is a list of ABAPS categorized by app. server and 
* work process type, and sorted by a number: how many times
* that particular ABAP was found running for too long time (>5min)
* during that period.
*
REPORT ZHEAVYLS.

DATA: INPUT_FILE(40) VALUE '/oracle/SID/sapreorg/heavy_abaps'.
PARAMETERS: DATE LIKE AMDS-ANDAT DEFAULT SY-DATUM,
            FROMTIME LIKE PLKZ-AEUZEIT DEFAULT SY-UZEIT,
            TOTIME LIKE PLKZ-AEUZEIT DEFAULT SY-UZEIT.

DATA: BEGIN OF O,
      1(10), 2(8), 3(8), 4(3), 5(8), 6(8),
END OF O.
DATA: BEGIN OF A OCCURS 100,
      3(8), 4(3), 6(8), NUM TYPE I,
END OF A.

OPEN DATASET INPUT_FILE FOR INPUT IN TEXT MODE.
DO.
  READ DATASET INPUT_FILE INTO O.
  IF SY-SUBRC <> 0.EXIT.ENDIF.
  IF O-1 = DATE AND O-2 >= FROMTIME AND O-2 <= TOTIME.
    MOVE-CORRESPONDING O TO A. A-NUM = 1.
    COLLECT A.
  ENDIF.
ENDDO.
CLOSE DATASET INPUT_FILE.

WRITE: / DATE, FROMTIME, '---', TOTIME.
SKIP 2.
SORT A BY 3 4 NUM DESCENDING.
LOOP AT A.
  AT NEW 3.
    WRITE: / A-3 COLOR 2.
  ENDAT.
  AT NEW 4.
    WRITE: / '      ',A-4 COLOR 3.
  ENDAT.
  WRITE: / '             ', A-6, A-NUM.
ENDLOOP.
