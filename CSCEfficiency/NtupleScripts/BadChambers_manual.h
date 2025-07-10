
  
  // Optional chamber removal
  if (deadChambersTrack){
    // ----- ME-42/4 -----
    // Dead Chamber All 2023-2024
    badChamber[0][0][4-1][2][4-1] = true;  badChamberRun[0][0][4-1][2][4-1][0] = firstRun;  badChamberRun[0][0][4-1][2][4-1][1] = lastRun;
  }


  if (badChambers2023Track && !autoRemoval) {


    if (badChambers2023Track2) {
      // ----- ME-11A/1 -----
      // Dead DCFEB 1-3 seg 43.04% LCT 42.05% all runs
      badChamber[0][0][1-1][0][1-1] = true;  badChamberRun[0][0][1-1][0][1-1][0] = firstRun;  badChamberRun[0][0][1-1][0][1-1][1] = lastRun;

      // ----- ME-11A/4 -----
      // Dead DCFEB 1-4 seg 31.81% LCT 31.20% all runs
      badChamber[0][0][1-1][0][4-1] = true;  badChamberRun[0][0][1-1][0][4-1][0] = firstRun;  badChamberRun[0][0][1-1][0][4-1][1] = lastRun;



      // ----- ME-11B/1 -----
      // Dead DCFEB 1-4 seg 40.60% LCT 39.73% all runs
      badChamber[0][0][1-1][1][1-1] = true;  badChamberRun[0][0][1-1][1][1-1][0] = firstRun;  badChamberRun[0][0][1-1][1][1-1][1] = lastRun;



      // ----- ME-11B/4 -----
      // Dead DCFEB 1-4 seg 34.01% LCT 33.69% all runs
      badChamber[0][0][1-1][1][1-1] = true;  badChamberRun[0][0][1-1][1][1-1][0] = firstRun;  badChamberRun[0][0][1-1][1][1-1][1] = lastRun;



      // ----- ME-11A/20 -----
      // Dead DCFEB 1 seg 2.70% LCT 13.31% all runs
      // Dead DCFEB 3 seg 4.35% LCT 12.54% all runs
      // only would leave 2
      badChamber[0][0][1-1][0][20-1] = true;  badChamberRun[0][0][1-1][0][20-1][0] = firstRun;  badChamberRun[0][0][1-1][0][20-1][1] = lastRun;


      // ----- ME-42/20 -----
      // ME-42/20 LCT 50%
      badChamber[0][0][4-1][2][19-1] = true;  badChamberRun[0][0][4-1][2][19-1][0] = firstRun;  badChamberRun[0][0][4-1][2][19-1][1] = lastRun;




    }


    // ----- ME+31/15 -----
    // Dead DCFEB 1 seg 71.23% all runs
    // go from 1-5

    // Dead DCFEB 4 seg 78.83% all runs
    // removed for 31 study
    badChamber[0][1][3-1][1][15-1] = true;  badChamberRun[0][1][3-1][1][15-1][0] = firstRun;  badChamberRun[0][1][3-1][1][15-1][1] = lastRun;


    // ----- ME-11A/19 -----
    // Dead DCFEB 3 seg 7.75% all runs
    badChamber[0][0][1-1][0][19-1] = true;  badChamberRun[0][0][1-1][0][19-1][0] = firstRun;  badChamberRun[0][0][1-1][0][19-1][1] = lastRun;  badChamberLCS[0][0][1-1][0][19-1][0] = 30.00;  badChamberLCS[0][0][1-1][0][19-1][1] = 50.00;



    // ----- ME-12/6 -----
    // Dead DCFEB 4 seg 67.92% LCT 67.46% all runs
    badChamber[0][0][1-1][2][6-1] = true;  badChamberRun[0][0][1-1][2][6-1][0] = firstRun;  badChamberRun[0][0][1-1][2][6-1][1] = lastRun;  badChamberLCS[0][0][1-1][2][6-1][0] = 46.00;  badChamberLCS[0][0][1-1][2][6-1][1] = 66.00;


    // ----- ME-12/27 -----
    // Dead DCFEB 1 seg 13.36% LCT 16.28% all runs
    badChamber[0][0][1-1][2][27-1] = true;  badChamberRun[0][0][1-1][2][27-1][0] = firstRun;  badChamberRun[0][0][1-1][2][27-1][1] = lastRun;  badChamberLCS[0][0][1-1][2][27-1][0] = -2.00;  badChamberLCS[0][0][1-1][2][27-1][1] = 18.00;


    // ----- ME-12/30 -----
    //  Dead DCFEB 1 LCT 77.56% all runs
    badChamber[0][0][1-1][2][30-1] = true;  badChamberRun[0][0][1-1][2][30-1][0] = firstRun;  badChamberRun[0][0][1-1][2][30-1][1] = lastRun;  badChamberLCS[0][0][1-1][2][30-1][0] = -2.00;  badChamberLCS[0][0][1-1][2][30-1][1] = 18.00;


    // ----- ME-12/33 -----
    // Dead DCFEB 1 seg 12.40% LCT 15.31% all runs
    badChamber[0][0][1-1][2][33-1] = true;  badChamberRun[0][0][1-1][2][33-1][0] = firstRun;  badChamberRun[0][0][1-1][2][33-1][1] = lastRun;  badChamberLCS[0][0][1-1][2][33-1][0] = -2.00;  badChamberLCS[0][0][1-1][2][33-1][1] = 18.00;


    // ----- ME-13/30 -----
    //  Dead DCFEB 2 LCT 68.17% all runs
    //  go from 2-3
    //badChamber[0][0][1-1][3][30-1] = true;  badChamberRun[0][0][1-1][3][30-1][0] = firstRun;  badChamberRun[0][0][1-1][3][30-1][1] = lastRun;  badChamberLCS[0][0][1-1][3][30-1][0] = 14.00;  badChamberLCS[0][0][1-1][3][30-1][1] = 34.00;

    //  Dead DCFEB 4 LCT 65.61% all runs
    badChamber[0][0][1-1][3][30-1] = true;  badChamberRun[0][0][1-1][3][30-1][0] = firstRun;  badChamberRun[0][0][1-1][3][30-1][1] = lastRun;  badChamberLCS[0][0][1-1][3][30-1][0] = 14.00;  badChamberLCS[0][0][1-1][3][30-1][1] = 66.00;



    // ----- ME-21/12 -----
    // Dead DCFEB 1 seg 71.31% all runs
    badChamber[0][0][2-1][1][12-1] = true;  badChamberRun[0][0][2-1][1][12-1][0] = firstRun;  badChamberRun[0][0][2-1][1][12-1][1] = lastRun;  badChamberLCS[0][0][2-1][1][12-1][0] = -2.00;  badChamberLCS[0][0][2-1][1][12-1][1] = 18.00;


    // ----- ME-21/15 -----
    // Dead DCFEB 1 seg 3.55% LCT 5.11% all runs
    badChamber[0][0][2-1][1][15-1] = true;  badChamberRun[0][0][2-1][1][15-1][0] = firstRun;  badChamberRun[0][0][2-1][1][15-1][1] = lastRun;  badChamberLCS[0][0][2-1][1][15-1][0] = -2.00;  badChamberLCS[0][0][2-1][1][15-1][1] = 18.00;


    // ----- ME-22/3 -----
    // Dead DCFEB 2 seg 11.24% all runs
    badChamber[0][0][2-1][2][3-1] = true;  badChamberRun[0][0][2-1][2][3-1][0] = firstRun;  badChamberRun[0][0][2-1][2][3-1][1] = lastRun;  badChamberLCS[0][0][2-1][2][3-1][0] = 14.00;  badChamberLCS[0][0][2-1][2][3-1][1] = 34.00;


    // ----- ME-31/3 -----
    // Dead DCFEB 1 seg 72.17% all runs
    badChamber[0][0][3-1][1][3-1] = true;  badChamberRun[0][0][3-1][1][3-1][0] = firstRun;  badChamberRun[0][0][3-1][1][3-1][1] = lastRun;  badChamberLCS[0][0][3-1][1][3-1][0] = -2.00;  badChamberLCS[0][0][3-1][1][3-1][1] = 18.00;


    // ----- ME-31/4 -----
    // Dead DCFEB 3 seg 79.61% all runs, and a bunch of other junk
    //badChamber[0][0][3-1][1][4-1] = true;  badChamberRun[0][0][3-1][1][4-1][0] = firstRun;  badChamberRun[0][0][3-1][1][4-1][1] = lastRun;  badChamberLCS[0][0][3-1][1][4-1][0] = 30.00;  badChamberLCS[0][0][3-1][1][4-1][1] = 50.00;
    // removed for 31 study
    badChamber[0][0][3-1][1][4-1] = true;  badChamberRun[0][0][3-1][1][4-1][0] = firstRun;  badChamberRun[0][0][3-1][1][4-1][1] = lastRun;

    // ----- ME-32/19 -----
    // Dead DCFEB 4 seg 8.07% LCT 4.91% all runs
    badChamber[0][0][3-1][2][19-1] = true;  badChamberRun[0][0][3-1][2][19-1][0] = firstRun;  badChamberRun[0][0][3-1][2][19-1][1] = lastRun;  badChamberLCS[0][0][3-1][2][19-1][0] = 46.00;  badChamberLCS[0][0][3-1][2][19-1][1] = 66.00;


    // ----- ME-32/27 -----
    //  Dead DCFEB 4 LCT 70.83% all runs
    badChamber[0][0][3-1][2][27-1] = true;  badChamberRun[0][0][3-1][2][27-1][0] = firstRun;  badChamberRun[0][0][3-1][2][27-1][1] = lastRun;  badChamberLCS[0][0][3-1][2][27-1][0] = 46.00;  badChamberLCS[0][0][3-1][2][27-1][1] = 66.00;


    // ----- ME-32/30 -----
    //  Dead DCFEB 5 LCT 72.47% all runs
    badChamber[0][0][3-1][2][30-1] = true;  badChamberRun[0][0][3-1][2][30-1][0] = firstRun;  badChamberRun[0][0][3-1][2][30-1][1] = lastRun;  badChamberLCS[0][0][3-1][2][30-1][0] = 62.00;  badChamberLCS[0][0][3-1][2][30-1][1] = 82.00;


    // ----- ME-41/10 -----
    // Dead DCFEB 1 seg 76.50% all runs
    badChamber[0][0][4-1][1][10-1] = true;  badChamberRun[0][0][4-1][1][10-1][0] = firstRun;  badChamberRun[0][0][4-1][1][10-1][1] = lastRun;  badChamberLCS[0][0][4-1][1][10-1][0] = -2.00;  badChamberLCS[0][0][4-1][1][10-1][1] = 18.00;


    // ----- ME-41/17 -----
    // Dead DCFEB 4 seg 4.47% LCT 4.90% all runs
    badChamber[0][0][4-1][1][17-1] = true;  badChamberRun[0][0][4-1][1][17-1][0] = firstRun;  badChamberRun[0][0][4-1][1][17-1][1] = lastRun;  badChamberLCS[0][0][4-1][1][17-1][0] = 46.00;  badChamberLCS[0][0][4-1][1][17-1][1] = 66.00;


    // ----- ME-42/4 -----
    // Dead Chamber
    badChamber[0][0][4-1][2][4-1] = true;  badChamberRun[0][0][4-1][2][4-1][0] = firstRun;  badChamberRun[0][0][4-1][2][4-1][1] = lastRun;


    // ----- ME-42/27 -----
    // Dead DCFEB 3 seg 15.82% LCT 13.30% all runs
    badChamber[0][0][4-1][2][27-1] = true;  badChamberRun[0][0][4-1][2][27-1][0] = firstRun;  badChamberRun[0][0][4-1][2][27-1][1] = lastRun;  badChamberLCS[0][0][4-1][2][27-1][0] = 30.00;  badChamberLCS[0][0][4-1][2][27-1][1] = 50.00;


    // ----- ME+11A/33 -----
    // Dead DCFEB 1 seg 77.25% all runs
    badChamber[0][1][1-1][0][33-1] = true;  badChamberRun[0][1][1-1][0][33-1][0] = firstRun;  badChamberRun[0][1][1-1][0][33-1][1] = lastRun;  badChamberLCS[0][1][1-1][0][33-1][0] = -2.00;  badChamberLCS[0][1][1-1][0][33-1][1] = 18.00;


    // ----- ME+11B/12 -----
    // Dead DCFEB 3 seg 9.45% LCT 14.09% all runs
    badChamber[0][1][1-1][1][12-1] = true;  badChamberRun[0][1][1-1][1][12-1][0] = firstRun;  badChamberRun[0][1][1-1][1][12-1][1] = lastRun;  badChamberLCS[0][1][1-1][1][12-1][0] = 30.00;  badChamberLCS[0][1][1-1][1][12-1][1] = 50.00;


    // ----- ME+12/10 -----
    //  Dead DCFEB 3 LCT 64.13% all runs
    // Go from 3 - 5
    //badChamber[0][1][1-1][2][10-1] = true;  badChamberRun[0][1][1-1][2][10-1][0] = firstRun;  badChamberRun[0][1][1-1][2][10-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][10-1][0] = 30.00;  badChamberLCS[0][1][1-1][2][10-1][1] = 50.00;

    // Dead DCFEB 4 seg 75.38% LCT 56.92% all runs
    //badChamber[0][1][1-1][2][10-1] = true;  badChamberRun[0][1][1-1][2][10-1][0] = firstRun;  badChamberRun[0][1][1-1][2][10-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][10-1][0] = 46.00;  badChamberLCS[0][1][1-1][2][10-1][1] = 66.00;

    //  Dead DCFEB 5 LCT 66.84% all runs
    badChamber[0][1][1-1][2][10-1] = true;  badChamberRun[0][1][1-1][2][10-1][0] = firstRun;  badChamberRun[0][1][1-1][2][10-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][10-1][0] = 30.00;  badChamberLCS[0][1][1-1][2][10-1][1] = 82.00;


    // ----- ME+12/13 -----
    // Dead DCFEB 5 seg 5.84% all runs
    badChamber[0][1][1-1][2][13-1] = true;  badChamberRun[0][1][1-1][2][13-1][0] = firstRun;  badChamberRun[0][1][1-1][2][13-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][13-1][0] = 62.00;  badChamberLCS[0][1][1-1][2][13-1][1] = 82.00;


    // ----- ME+12/15 -----
    // Dead DCFEB 1 seg 9.01% all runs
    badChamber[0][1][1-1][2][15-1] = true;  badChamberRun[0][1][1-1][2][15-1][0] = firstRun;  badChamberRun[0][1][1-1][2][15-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][15-1][0] = -2.00;  badChamberLCS[0][1][1-1][2][15-1][1] = 18.00;


    // ----- ME+12/21 -----
    // Dead DCFEB 2 seg 4.44% LCT 2.61% all runs
    // Go from 2-4
    //badChamber[0][1][1-1][2][21-1] = true;  badChamberRun[0][1][1-1][2][21-1][0] = firstRun;  badChamberRun[0][1][1-1][2][21-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][21-1][0] = 14.00;  badChamberLCS[0][1][1-1][2][21-1][1] = 34.00;

    // Dead DCFEB 4 seg 25.81% LCT 23.66% all runs
    badChamber[0][1][1-1][2][21-1] = true;  badChamberRun[0][1][1-1][2][21-1][0] = firstRun;  badChamberRun[0][1][1-1][2][21-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][21-1][0] = 14.00;  badChamberLCS[0][1][1-1][2][21-1][1] = 66.00;


    // ----- ME+12/31 -----
    // Dead DCFEB 5 seg 12.47% LCT 11.23% all runs
    badChamber[0][1][1-1][2][31-1] = true;  badChamberRun[0][1][1-1][2][31-1][0] = firstRun;  badChamberRun[0][1][1-1][2][31-1][1] = lastRun;  badChamberLCS[0][1][1-1][2][31-1][0] = 62.00;  badChamberLCS[0][1][1-1][2][31-1][1] = 82.00;


    // ----- ME+13/11 -----
    // Dead DCFEB 3 seg 10.15% all runs
    badChamber[0][1][1-1][3][11-1] = true;  badChamberRun[0][1][1-1][3][11-1][0] = firstRun;  badChamberRun[0][1][1-1][3][11-1][1] = lastRun;  badChamberLCS[0][1][1-1][3][11-1][0] = 30.00;  badChamberLCS[0][1][1-1][3][11-1][1] = 50.00;

    // ----- ME+21/11 -----
    // Run dependent
    badChamber[0][1][2-1][1][11-1] = true;  badChamberRun[0][1][2-1][1][11-1][0] = 367300;  badChamberRun[0][1][2-1][1][11-1][1] = 367400;
    // Found as part of ME21 study



    // ----- ME+22/5 -----
    // Dead DCFEB 1 seg 12.78% LCT 22.68% all runs
    badChamber[0][1][2-1][2][5-1] = true;  badChamberRun[0][1][2-1][2][5-1][0] = firstRun;  badChamberRun[0][1][2-1][2][5-1][1] = lastRun;  badChamberLCS[0][1][2-1][2][5-1][0] = -2.00;  badChamberLCS[0][1][2-1][2][5-1][1] = 18.00;


    // ----- ME+22/15 -----
    // Dead DCFEB 5 seg 7.79% LCT 4.23% all runs
    badChamber[0][1][2-1][2][15-1] = true;  badChamberRun[0][1][2-1][2][15-1][0] = firstRun;  badChamberRun[0][1][2-1][2][15-1][1] = lastRun;  badChamberLCS[0][1][2-1][2][15-1][0] = 62.00;  badChamberLCS[0][1][2-1][2][15-1][1] = 82.00;


    // ----- ME+22/19 -----
    // Dead DCFEB 5 seg 9.80% LCT 6.60% all runs
    badChamber[0][1][2-1][2][19-1] = true;  badChamberRun[0][1][2-1][2][19-1][0] = firstRun;  badChamberRun[0][1][2-1][2][19-1][1] = lastRun;  badChamberLCS[0][1][2-1][2][19-1][0] = 62.00;  badChamberLCS[0][1][2-1][2][19-1][1] = 82.00;


    // ----- ME+22/36 -----
    //  Dead DCFEB 1 LCT 74.45% all runs
    badChamber[0][1][2-1][2][36-1] = true;  badChamberRun[0][1][2-1][2][36-1][0] = firstRun;  badChamberRun[0][1][2-1][2][36-1][1] = lastRun;  badChamberLCS[0][1][2-1][2][36-1][0] = -2.00;  badChamberLCS[0][1][2-1][2][36-1][1] = 18.00;



    // ----- ME+32/19 -----
    // Dead DCFEB 5 seg 6.47% LCT 3.34% all runs
    badChamber[0][1][3-1][2][19-1] = true;  badChamberRun[0][1][3-1][2][19-1][0] = firstRun;  badChamberRun[0][1][3-1][2][19-1][1] = lastRun;  badChamberLCS[0][1][3-1][2][19-1][0] = 62.00;  badChamberLCS[0][1][3-1][2][19-1][1] = 82.00;


    // ----- ME+32/29 -----
    // Dead DCFEB 4 seg 55.92% LCT 50.27% all runs
    badChamber[0][1][3-1][2][29-1] = true;  badChamberRun[0][1][3-1][2][29-1][0] = firstRun;  badChamberRun[0][1][3-1][2][29-1][1] = lastRun;  badChamberLCS[0][1][3-1][2][29-1][0] = 46.00;  badChamberLCS[0][1][3-1][2][29-1][1] = 66.00;


    // ----- ME+41/4 -----
    // Dead DCFEB 4 seg 10.31% all runs
    badChamber[0][1][4-1][1][4-1] = true;  badChamberRun[0][1][4-1][1][4-1][0] = firstRun;  badChamberRun[0][1][4-1][1][4-1][1] = lastRun;  badChamberLCS[0][1][4-1][1][4-1][0] = 46.00;  badChamberLCS[0][1][4-1][1][4-1][1] = 66.00;


    // ----- ME+41/9 -----
    // Dead DCFEB 2 seg 77.17% all runs
    badChamber[0][1][4-1][1][9-1] = true;  badChamberRun[0][1][4-1][1][9-1][0] = firstRun;  badChamberRun[0][1][4-1][1][9-1][1] = lastRun;  badChamberLCS[0][1][4-1][1][9-1][0] = 14.00;  badChamberLCS[0][1][4-1][1][9-1][1] = 34.00;


    // ----- ME+42/1 -----
    // Dead DCFEB 5 seg 13.36% LCT 13.47% all runs
    badChamber[0][1][4-1][2][1-1] = true;  badChamberRun[0][1][4-1][2][1-1][0] = firstRun;  badChamberRun[0][1][4-1][2][1-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][1-1][0] = 62.00;  badChamberLCS[0][1][4-1][2][1-1][1] = 82.00;


    // ----- ME+42/2 -----
    // Dead DCFEB 1 seg 69.48% LCT 50.14% all runs
    // Remove lower eff DCFEB
    badChamber[0][1][4-1][2][2-1] = true;  badChamberRun[0][1][4-1][2][2-1][0] = firstRun;  badChamberRun[0][1][4-1][2][2-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][2-1][0] = -2.00;  badChamberLCS[0][1][4-1][2][2-1][1] = 18.00;

    //  Dead DCFEB 5 LCT 74.80% all runs
    //badChamber[0][1][4-1][2][2-1] = true;  badChamberRun[0][1][4-1][2][2-1][0] = firstRun;  badChamberRun[0][1][4-1][2][2-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][2-1][0] = 62.00;  badChamberLCS[0][1][4-1][2][2-1][1] = 82.00;


    // ----- ME+42/6 -----
    // Dead DCFEB 3 seg 12.02% LCT 9.18% all runs
    badChamber[0][1][4-1][2][6-1] = true;  badChamberRun[0][1][4-1][2][6-1][0] = firstRun;  badChamberRun[0][1][4-1][2][6-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][6-1][0] = 30.00;  badChamberLCS[0][1][4-1][2][6-1][1] = 50.00;


    // ----- ME+42/22 -----
    // Dead DCFEB 1 seg 61.23% LCT 62.96% all runs
    badChamber[0][1][4-1][2][22-1] = true;  badChamberRun[0][1][4-1][2][22-1][0] = firstRun;  badChamberRun[0][1][4-1][2][22-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][22-1][0] = -2.00;  badChamberLCS[0][1][4-1][2][22-1][1] = 18.00;


    // ----- ME+42/23 -----
    // Dead DCFEB 3 seg 77.91% LCT 76.06% all runs
    badChamber[0][1][4-1][2][23-1] = true;  badChamberRun[0][1][4-1][2][23-1][0] = firstRun;  badChamberRun[0][1][4-1][2][23-1][1] = lastRun;  badChamberLCS[0][1][4-1][2][23-1][0] = 30.00;  badChamberLCS[0][1][4-1][2][23-1][1] = 50.00;


  }

  // New dead chamber Run 3 2023 hand generated
  bool badChambers2023TrackOld = false;

  // Check if this works, I had it wrong
  if (badChambers2023TrackOld) {

    // New bad (D)CFEBs Run 3 and run ranges


    badChamber[0][0][4-1][2][4-1] = true;   badChamberRun[0][0][4-1][2][4-1][0] = firstRun; badChamberRun[0][0][4-1][2][4-1][1] = lastRun; // ME-42/04  Came back right at the end, has this been fixed?  No, still dead 2023


    // New bad (D)CFEBs Run 3 and run ranges

    // ME+42
    badChamber[0][1][4-1][2][1-1] = true;   badChamberRun[0][1][4-1][2][1-1][0] = firstRun; badChamberRun[0][1][4-1][2][1-1][1] = lastRun; badChamberLCS[0][1][4-1][2][1-1][0] = 62.0; badChamberLCS[0][1][4-1][2][1-1][1] = 82.0;// ME+42/1 DCFEB 5 all runs

    badChamber[0][1][4-1][2][2-1] = true;   badChamberRun[0][1][4-1][2][2-1][0] = firstRun; badChamberRun[0][1][4-1][2][2-1][1] = lastRun; badChamberLCS[0][1][4-1][2][2-1][0] = -2.0; badChamberLCS[0][1][4-1][2][2-1][1] = 18.0;// ME+42/2 50% eff DCFEB 1, all runs
                                                                                                                                                                                                                                  // !!!!! Not removing DCFEB 5 74%

    badChamber[0][1][4-1][2][6-1] = true;   badChamberRun[0][1][4-1][2][6-1][0] = firstRun; badChamberRun[0][1][4-1][2][6-1][1] = lastRun; badChamberLCS[0][1][4-1][2][6-1][0] = 30.0; badChamberLCS[0][1][4-1][2][6-1][1] = 50.0;// ME+42/6 DCFEB 3 all runs

    badChamber[0][1][4-1][2][22-1] = true;   badChamberRun[0][1][4-1][2][22-1][0] = firstRun; badChamberRun[0][1][4-1][2][22-1][1] = lastRun; badChamberLCS[0][1][4-1][2][22-1][0] = -2.0; badChamberLCS[0][1][4-1][2][22-1][1] = 18.0;// ME+42/22 DCFEB 1 partially bad 70%, now all runs


    //ME+41
    badChamber[0][1][4-1][1][4-1] = true;   badChamberRun[0][1][4-1][1][4-1][0] = firstRun; badChamberRun[0][1][4-1][1][4-1][1] = lastRun; badChamberLCS[0][1][4-1][1][4-1][0] = 46.0; badChamberLCS[0][1][4-1][1][4-1][1] = 66.0;// ME+42/4 DCFEB 4 all runs

    // ME+32
    badChamber[0][1][3-1][2][19-1] = true;   badChamberRun[0][1][3-1][2][19-1][0] = firstRun; badChamberRun[0][1][3-1][2][19-1][1] = lastRun; badChamberLCS[0][1][3-1][2][19-1][0] = 62.0; badChamberLCS[0][1][3-1][2][19-1][1] = 82.0;// ME+32/19 DCFEB 5 all runs

    badChamber[0][1][3-1][2][29-1] = true;   badChamberRun[0][1][3-1][2][29-1][0] = firstRun; badChamberRun[0][1][3-1][2][29-1][1] = lastRun; badChamberLCS[0][1][3-1][2][29-1][0] = 46.0; badChamberLCS[0][1][3-1][2][29-1][1] = 66.0;// ME+32/29 DCFEB 4 all runs

    badChamber[0][1][3-1][1][15-1] = true;   badChamberRun[0][1][3-1][1][15-1][0] = firstRun; badChamberRun[0][1][3-1][1][15-1][1] = lastRun; badChamberLCS[0][1][3-1][1][15-1][0] = 62.0; badChamberLCS[0][1][3-1][1][15-1][1] = 82.0;// ME+31/15 30% all runs

    // ME+22
    badChamber[0][1][2-1][2][5-1] = true;   badChamberRun[0][1][2-1][2][5-1][0] = firstRun; badChamberRun[0][1][2-1][2][5-1][1] = lastRun; badChamberLCS[0][1][2-1][2][5-1][0] = -2.0; badChamberLCS[0][1][2-1][2][5-1][1] = 18.0;// ME+22/5 DCFEB 1 all runs

    badChamber[0][1][2-1][2][15-1] = true;   badChamberRun[0][1][2-1][2][15-1][0] = firstRun; badChamberRun[0][1][2-1][2][15-1][1] = lastRun; badChamberLCS[0][1][2-1][2][15-1][0] = 62.0; badChamberLCS[0][1][2-1][2][15-1][1] = 82.0;// ME+22/15 DCFEB 5 all runs

    badChamber[0][1][2-1][2][19-1] = true;   badChamberRun[0][1][2-1][2][19-1][0] = firstRun; badChamberRun[0][1][2-1][2][19-1][1] = lastRun; badChamberLCS[0][1][2-1][2][19-1][0] = 62.0; badChamberLCS[0][1][2-1][2][19-1][1] = 82.0;// ME+22/19 DCFEB 5 all runs


    // ME+21


    // ME+13
    badChamber[0][1][1-1][3][11-1] = true;   badChamberRun[0][1][1-1][3][11-1][0] = firstRun; badChamberRun[0][1][1-1][3][11-1][1] = lastRun; badChamberLCS[0][1][1-1][3][11-1][0] = 30.0; badChamberLCS[0][1][1-1][3][11-1][1] = 50.0;// ME+31/11 all runs, gen low LCT eff 89%


    // ME+12
    // ME+12/10 DCFEB 3,4,5 80% eff LCT worse
    badChamber[0][1][1-1][2][13-1] = true;   badChamberRun[0][1][1-1][2][13-1][0] = firstRun; badChamberRun[0][1][1-1][2][13-1][1] = lastRun; badChamberLCS[0][1][1-1][2][13-1][0] = 62.0; badChamberLCS[0][1][1-1][2][13-1][1] = 82.0;// ME+12/13 DCFEB 5 all runs

    badChamber[0][1][1-1][2][15-1] = true;   badChamberRun[0][1][1-1][2][15-1][0] = firstRun; badChamberRun[0][1][1-1][2][15-1][1] = lastRun; badChamberLCS[0][1][1-1][2][15-1][0] = -2.0; badChamberLCS[0][1][1-1][2][15-1][1] = 18.0;// ME+12/15 DCFEB 1


    badChamber[0][1][1-1][2][21-1] = true;   badChamberRun[0][1][1-1][2][21-1][0] = firstRun; badChamberRun[0][1][1-1][2][21-1][1] = lastRun; badChamberLCS[0][1][1-1][2][21-1][0] = 14.0; badChamberLCS[0][1][1-1][2][21-1][1] = 66.0;// ME+12/21 DCFEB 2,4 all runs, 2 80%, 4 40%

    badChamber[0][1][1-1][2][31-1] = true;   badChamberRun[0][1][1-1][2][31-1][0] = firstRun; badChamberRun[0][1][1-1][2][31-1][1] = lastRun; badChamberLCS[0][1][1-1][2][31-1][0] = 62.0; badChamberLCS[0][1][1-1][2][31-1][1] = 82.0;// ME+12/31 DCFEB 5 all runs



    // ME+11A/B
    // ME+11A/B-21 now low efficinecy more recent runs





    // ME+11A
    //badChamber[0][1][1-1][0][20-1] = true;  badChamberRun[0][1][1-1][0][20-1][0] = firstRun; badChamberRun[0][1][1-1][0][20-1][1] = lastRun; badChamberLCS[0][1][1-1][0][20-1][0] = -2.0; badChamberLCS[0][1][1-1][0][20-1][1] = 50.0;// DCFEB 1,3 LCT only ME-11A/20 all runs However, this is all the DCFEBs

    // ME+11B
    badChamber[0][1][1-1][1][12-1] = true;  badChamberRun[0][1][1-1][1][12-1][0] = firstRun; badChamberRun[0][1][1-1][1][12-1][1] = lastRun; badChamberLCS[0][1][1-1][1][12-1][0] = 30.0; badChamberLCS[0][1][1-1][1][12-1][1] = 50.0;// ME+11B/12 DCFEB 3 all runs


    // ME-11A
    badChamber[0][0][1-1][0][19-1] = true;  badChamberRun[0][0][1-1][0][19-1][0] = firstRun; badChamberRun[0][0][1-1][0][19-1][1] = lastRun; badChamberLCS[0][0][1-1][0][19-1][0] = 30.0; badChamberLCS[0][0][1-1][0][19-1][1] = 50.0;// ME-11A/19 all runs

    badChamber[0][0][1-1][0][20-1] = true;  badChamberRun[0][0][1-1][0][20-1][0] = firstRun; badChamberRun[0][0][1-1][0][20-1][1] = lastRun; badChamberLCS[0][0][1-1][0][20-1][0] = -2.0; badChamberLCS[0][0][1-1][0][20-1][1] = 18.0;// ME-11A/20 DCFEB 1 and 3 all runs however this only leaves 2

    // ME-11B
    badChamber[0][0][1-1][1][12-1] = true;  badChamberRun[0][0][1-1][1][12-1][0] = 366860; badChamberRun[0][0][1-1][1][12-1][1] = 366900; badChamberLCS[0][0][1-1][1][12-1][0] = 30.0; badChamberLCS[0][0][1-1][1][12-1][1] = 50.0;// ME-11B/12 DCFEB 3 all runs still leaves soem low eff DCFEBs 366860-366900


    // !!!!! May want to remove ME-11B/12 DCFEB 3 around 366800


    // ME-11A/B
    // Now ME-11AB/4 always inefficient
    //if (badRunRangesTrack) badChamber[0][0][1-1][1][4-1] = true;   badChamberRun[0][0][1-1][1][4-1][0] = 359602; badChamberRun[0][0][1-1][1][4-1][1] = 359814;// ME-11A/4 359602 to 359814
    //if (badRunRangesTrack) badChamber[0][0][1-1][0][4-1] = true;   badChamberRun[0][0][1-1][0][4-1][0] = 359602; badChamberRun[0][0][1-1][0][4-1][1] = 359814;// ME-11B/4 359602 to 359814

    // ME-11AB/23 40% LCT



    // ME-12

    badChamber[0][0][1-1][2][27-1] = true;  badChamberRun[0][0][1-1][2][27-1][0] = firstRun; badChamberRun[0][0][1-1][2][27-1][1] = lastRun; badChamberLCS[0][0][1-1][2][27-1][0] = -2.0; badChamberLCS[0][0][1-1][2][27-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs
    badChamber[0][0][1-1][2][33-1] = true;  badChamberRun[0][0][1-1][2][33-1][0] = firstRun; badChamberRun[0][0][1-1][2][33-1][1] = lastRun; badChamberLCS[0][0][1-1][2][33-1][0] = -2.0; badChamberLCS[0][0][1-1][2][33-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs


    // ME-13

    //!!!!! check this ME-13 30 low in 3 our of 4 (D)CFEBs for LCTs 83%

    // ME-21

    badChamber[0][0][2-1][1][15-1] = true;   badChamberRun[0][0][2-1][1][15-1][0] = firstRun; badChamberRun[0][0][2-1][1][15-1][1] = lastRun; badChamberLCS[0][0][2-1][1][15-1][0] = -2.0; badChamberLCS[0][0][2-1][1][15-1][1] = 18.0;// ME-21/15 DCFEB 1 all runs



    // ME-22
    badChamber[0][0][2-1][2][3-1] = true;   badChamberRun[0][0][2-1][2][3-1][0] = firstRun; badChamberRun[0][0][2-1][2][3-1][1] = lastRun; badChamberLCS[0][0][2-1][2][3-1][0] = 14.0; badChamberLCS[0][0][2-1][2][3-1][1] = 34.0;// ME-22/3 DCFEB 2 all runs, !!!!! check this gen low LCT 86%

    //ME-31
    badChamber[0][0][3-1][1][4-1] = true;   badChamberRun[0][0][3-1][1][4-1][0] = firstRun; badChamberRun[0][0][3-1][1][4-1][1] = 359000; badChamberLCS[0][0][3-1][1][4-1][0] = 14.0; badChamberLCS[0][0][3-1][1][4-1][1] = 34.0;// ME-31/4 DCFEB 4 all runs


    // ME-32
    badChamber[0][0][3-1][2][19-1] = true;   badChamberRun[0][0][3-1][2][19-1][0] = firstRun; badChamberRun[0][0][3-1][2][19-1][1] = lastRun; badChamberLCS[0][0][3-1][2][19-1][0] = 46.0; badChamberLCS[0][0][3-1][2][19-1][1] = 66.0;// ME-32/19 DCFEB 3 all runs

    // ME-41
    badChamber[0][0][4-1][1][7-1] = true;   badChamberRun[0][0][4-1][1][7-1][0] = firstRun; badChamberRun[0][0][4-1][1][7-1][1] = lastRun; badChamberLCS[0][0][4-1][1][7-1][0] = 62.0; badChamberLCS[0][0][4-1][1][7-1][1] = 82.0;// ME-41/7 DCFEB 5 all runs
    badChamber[0][0][4-1][1][17-1] = true;   badChamberRun[0][0][4-1][1][17-1][0] = firstRun; badChamberRun[0][0][4-1][1][17-1][1] = lastRun; badChamberLCS[0][0][4-1][1][17-1][0] = 46.0; badChamberLCS[0][0][4-1][1][17-1][1] = 66.0;// ME-41/17 DCFEB 4 now all reun



    // ME-42
    // ME-42/19 53% LCT only !!!!! check LCT

    badChamber[0][0][4-1][2][26-1] = true;   badChamberRun[0][0][4-1][2][26-1][0] = firstRun; badChamberRun[0][0][4-1][2][26-1][1] = lastRun ; badChamberLCS[0][0][4-1][2][26-1][0] = 46.0; badChamberLCS[0][0][4-1][2][26-1][1] = 66.0;// ME-42/26 DCFEB 6  all runs 54%


    badChamber[0][0][4-1][2][27-1] = true;   badChamberRun[0][0][4-1][2][27-1][0] = firstRun; badChamberRun[0][0][4-1][2][27-1][1] = lastRun ; badChamberLCS[0][0][4-1][2][27-1][0] = 30.0; badChamberLCS[0][0][4-1][2][27-1][1] = 50.0;// ME-42/27 DCFEB 3  all runs


    badChamber[0][0][4-1][2][30-1] = true;   badChamberRun[0][0][4-1][2][30-1][0] = 366800; badChamberRun[0][0][4-1][2][30-1][1] = lastRun ; badChamberLCS[0][0][4-1][2][30-1][0] = 30.0; badChamberLCS[0][0][4-1][2][30-1][1] = 50.0;// ME-42/30 DCFEB 1  after 366800


  }




  // ????? exclude 357734?  seen in multiple rings
  if (badChambersTrack && !autoRemoval) {

    //?????? need to test if any of these are back

    // New Dead Chambers Run 3
    badChamber[0][1][1-1][2][10-1] = true;   badChamberRun[0][1][1-1][2][10-1][0] = firstRun; badChamberRun[0][1][1-1][2][10-1][1] = lastRun; // ME+12/10

    badChamber[0][1][2-1][2][31-1] = true;   badChamberRun[0][1][2-1][2][31-1][0] = firstRun; badChamberRun[0][1][2-1][2][31-1][1] = lastRun; // ME+22/31 Came back right at the end, has this been fixed

    badChamber[0][0][4-1][2][4-1] = true;   badChamberRun[0][0][4-1][2][4-1][0] = firstRun; badChamberRun[0][0][4-1][2][4-1][1] = lastRun; // ME-42/04  Came back right at the end, has this been fixed?


    // New bad (D)CFEBs Run 3 and run ranges

    // ME+42
    badChamber[0][1][4-1][2][1-1] = true;   badChamberRun[0][1][4-1][2][1-1][0] = firstRun; badChamberRun[0][1][4-1][2][1-1][1] = lastRun; badChamberLCS[0][1][4-1][2][1-1][0] = 62.0; badChamberLCS[0][1][4-1][2][1-1][1] = 82.0;// ME+42/1 all runs, good around 359000

    badChamber[0][1][4-1][2][2-1] = true;   badChamberRun[0][1][4-1][2][2-1][0] = firstRun; badChamberRun[0][1][4-1][2][2-1][1] = lastRun; badChamberLCS[0][1][4-1][2][2-1][0] = -2.0; badChamberLCS[0][1][4-1][2][2-1][1] = 18.0;// ME+42/2 50% eff DCFEB 1, all runs, good around 359000

    if (badRunRangesTrack) badChamber[0][1][4-1][2][3-1] = true;   badChamberRun[0][1][4-1][2][3-1][0] = 356466; badChamberRun[0][1][4-1][2][3-1][1] = 357734;// ME+42/3 two bad run regions, 356466-356490, 357328-357734

    badChamber[0][1][4-1][2][6-1] = true;   badChamberRun[0][1][4-1][2][6-1][0] = firstRun; badChamberRun[0][1][4-1][2][6-1][1] = lastRun; badChamberLCS[0][1][4-1][2][6-1][0] = 30.0; badChamberLCS[0][1][4-1][2][6-1][1] = 50.0;// ME+42/6 DCFEB 3 all runs

    badChamber[0][1][4-1][2][22-1] = true;   badChamberRun[0][1][4-1][2][22-1][0] = firstRun; badChamberRun[0][1][4-1][2][22-1][1] = 362300; badChamberLCS[0][1][4-1][2][22-1][0] = -2.0; badChamberLCS[0][1][4-1][2][22-1][1] = 18.0;// ME+42/22 DCFEB 1 partially bad 70%, okay after 362300


    //ME+41
    badChamber[0][1][4-1][1][4-1] = true;   badChamberRun[0][1][4-1][1][4-1][0] = firstRun; badChamberRun[0][1][4-1][1][4-1][1] = lastRun; badChamberLCS[0][1][4-1][1][4-1][0] = 46.0; badChamberLCS[0][1][4-1][1][4-1][1] = 66.0;// ME+42/4 DCFEB 4 all runs

    badChamber[0][1][4-1][1][9-1] = true;   badChamberRun[0][1][4-1][1][9-1][0] = 359700; badChamberRun[0][1][4-1][1][9-1][1] = lastRun; badChamberLCS[0][1][4-1][1][9-1][0] = 14.0; badChamberLCS[0][1][4-1][1][9-1][1] = 34.0;// ME+42/4 DCFEB 2 ~359700-lastRun partially bad 50%

    badChamber[0][1][4-1][1][12-1] = true;   badChamberRun[0][1][4-1][1][12-1][0] = 362088; badChamberRun[0][1][4-1][1][12-1][1] = 362108; // ME+42/12 bad run range 362088-362108
                                                                                                                                           // ME+41-15 also a few bad run ranges but less so

                                                                                                                                           // ME+32
    badChamber[0][1][3-1][2][19-1] = true;   badChamberRun[0][1][3-1][2][19-1][0] = firstRun; badChamberRun[0][1][3-1][2][19-1][1] = lastRun; badChamberLCS[0][1][3-1][2][19-1][0] = 62.0; badChamberLCS[0][1][3-1][2][19-1][1] = 82.0;// ME+32/19 DCFEB 5 all runs

    badChamber[0][1][3-1][2][24-1] = true;   badChamberRun[0][1][3-1][2][24-1][0] = 358500; badChamberRun[0][1][3-1][2][24-1][1] = lastRun; badChamberLCS[0][1][3-1][2][24-1][0] = 30.0; badChamberLCS[0][1][3-1][2][24-1][1] = 50.0;// ME+32/24 DCFEB 3 okay before 358500?????

    badChamber[0][1][3-1][2][29-1] = true;   badChamberRun[0][1][3-1][2][29-1][0] = firstRun; badChamberRun[0][1][3-1][2][29-1][1] = lastRun; badChamberLCS[0][1][3-1][2][29-1][0] = 46.0; badChamberLCS[0][1][3-1][2][29-1][1] = 66.0;// ME+32/29 DCFEB 4 all runs good around 359000
                                                                                                                                                                                                                                       // ME+32-31 maybe a bad DCFEB 1 right at the start then fixed
    badChamber[0][1][3-1][2][33-1] = true;   badChamberRun[0][1][3-1][2][33-1][0] = 356476; badChamberRun[0][1][3-1][2][33-1][1] = 356490; // ME+32-33 bad run range 356476-356490 same as chamber 34
    badChamber[0][1][3-1][2][33-1] = true;   badChamberRun[0][1][3-1][2][34-1][0] = 356476; badChamberRun[0][1][3-1][2][34-1][1] = 356490; // ME+32-34 bad run range 356476-356490 same as chamber 33


    // ME+31
    badChamber[0][1][3-1][1][5-1] = true;   badChamberRun[0][1][3-1][1][5-1][0] = 359570; badChamberRun[0][1][3-1][1][5-1][1] = 360226; // ME+31/5 // HV problem

    //ME+31/10 // 88% efficieincy no obvious reason other than OOS
    badChamber[0][1][3-1][1][10-1] = true;   badChamberRun[0][1][3-1][1][10-1][0] = 360942; badChamberRun[0][1][3-1][1][10-1][1] = 360952; // ME+31/10 // 0% eff in 360942-360952
                                                                                                                                           //ME+31/12 // 89% efficieincy no obvious reason other than OOS
    badChamber[0][1][3-1][1][13-1] = true;   badChamberRun[0][1][3-1][1][13-1][0] = 362148; badChamberRun[0][1][3-1][1][10-1][1] = 362168; // ME+31/13 0% in 362148-362168

    badChamber[0][1][3-1][1][15-1] = true;   badChamberRun[0][1][3-1][1][15-1][0] = firstRun; badChamberRun[0][1][3-1][1][15-1][1] = lastRun; badChamberLCS[0][1][3-1][1][15-1][0] = 62.0; badChamberLCS[0][1][3-1][1][15-1][1] = 82.0;// ME+31/15 30% all runs

    badChamber[0][1][3-1][1][17-1] = true;   badChamberRun[0][1][3-1][1][17-1][0] = 356310; badChamberRun[0][1][3-1][1][17-1][1] = 357734; // ME+31/17 three regions of bad efficiency.  Capture 2 of them 356310-356490, 357070-357734, 361050-361110

    // ME+22
    badChamber[0][1][2-1][2][5-1] = true;   badChamberRun[0][1][2-1][2][5-1][0] = firstRun; badChamberRun[0][1][2-1][2][5-1][1] = lastRun; badChamberLCS[0][1][2-1][2][5-1][0] = -2.0; badChamberLCS[0][1][2-1][2][5-1][1] = 18.0;// ME+22/5 DCFEB 1 all runs good around 359000

    badChamber[0][1][2-1][2][15-1] = true;   badChamberRun[0][1][2-1][2][15-1][0] = firstRun; badChamberRun[0][1][2-1][2][15-1][1] = lastRun; badChamberLCS[0][1][2-1][2][15-1][0] = 62.0; badChamberLCS[0][1][2-1][2][15-1][1] = 82.0;// ME+22/15 DCFEB 5 all runs good around 359000, there is a second DCFEB with smaller problems that I am ignoring. ????? check run range

    badChamber[0][1][2-1][2][19-1] = true;   badChamberRun[0][1][2-1][2][19-1][0] = firstRun; badChamberRun[0][1][2-1][2][19-1][1] = lastRun; badChamberLCS[0][1][2-1][2][19-1][0] = 62.0; badChamberLCS[0][1][2-1][2][19-1][1] = 82.0;// ME+22/19 DCFEB 5 all runs


    badChamber[0][1][2-1][2][27-1] = true;   badChamberRun[0][1][2-1][2][27-1][0] = 356476; badChamberRun[0][1][2-1][2][27-1][1] = 356490; // ME+22/27 in 356476-356490 also in chamber 28
    badChamber[0][1][2-1][2][28-1] = true;   badChamberRun[0][1][2-1][2][28-1][0] = 356476; badChamberRun[0][1][2-1][2][28-1][1] = 356490; // ME+22/27 in 356476-356490 also in chamber 27


    // ME+21

    if (badRunRangesTrack) badChamber[0][1][2-1][1][2-1] = true;   badChamberRun[0][1][2-1][1][2-1][0] = 355912; badChamberRun[0][1][2-1][1][2-1][1] = 355942;// ME+21/2 for 355912 to 355942

    if (badRunRangesTrack) badChamber[0][1][2-1][1][3-1] = true;   badChamberRun[0][1][2-1][1][3-1][0] = 356946; badChamberRun[0][1][2-1][1][3-1][1] = 357272;// ME+21/3 for 356946 to 357272

    badChamber[0][1][2-1][1][5-1] = true;   badChamberRun[0][1][2-1][1][5-1][0] = 357734; badChamberRun[0][1][2-1][1][5-1][1] = 360226; // ME+21/5 // HV problem E+F 357734-360226

    badChamber[0][1][2-1][1][6-1] = true;   badChamberRun[0][1][2-1][1][6-1][0] = firstRun; badChamberRun[0][1][2-1][1][6-1][1] = lastRun; badChamberLCS[0][1][2-1][1][6-1][0] = 30.0; badChamberLCS[0][1][2-1][1][6-1][1] = 50.0;// ME+21/6 all runs

    if (badRunRangesTrack) badChamber[0][1][2-1][1][11-1] = true;   badChamberRun[0][1][2-1][1][11-1][0] = 355118; badChamberRun[0][1][2-1][1][11-1][1] = 355560;// ME+21/11 four run ranges 355118-355560, 357438-357448, 357538-357734, 361298-361334 capture first 0 area,  Also 0-100% 50% ave eff LCT around 361300

    // ME+13
    // ME+13/10 LCT 89% no dependence
    badChamber[0][1][1-1][3][11-1] = true;   badChamberRun[0][1][1-1][3][11-1][0] = firstRun; badChamberRun[0][1][1-1][3][11-1][1] = lastRun; badChamberLCS[0][1][1-1][3][11-1][0] = 30.0; badChamberLCS[0][1][1-1][3][11-1][1] = 50.0;// ME+31/11 all runs good around 359000, gen low LCT eff 89%

    badChamber[0][1][1-1][3][12-1] = true;   badChamberRun[0][1][1-1][3][12-1][0] = 357734; badChamberRun[0][1][1-1][3][12-1][1] = 361958; // ME+13/12 for 357734-361958

    badChamber[0][1][1-1][3][20-1] = true;   badChamberRun[0][1][1-1][3][20-1][0] = firstRun; badChamberRun[0][1][1-1][3][20-1][1] = lastRun; badChamberLCS[0][1][1-1][3][20-1][0] = -2.0; badChamberLCS[0][1][1-1][3][20-1][1] = 18.0;// ME+31/20 DCFEB 1 70%
                                                                                                                                                                                                                                       // ME+13/30 LCT only 90%


                                                                                                                                                                                                                                       // ME+12
    badChamber[0][1][1-1][2][13-1] = true;   badChamberRun[0][1][1-1][2][13-1][0] = firstRun; badChamberRun[0][1][1-1][2][13-1][1] = lastRun; badChamberLCS[0][1][1-1][2][13-1][0] = 62.0; badChamberLCS[0][1][1-1][2][13-1][1] = 82.0;// ME+12/13 DCFEB 5 all runs good around 359000

    badChamber[0][1][1-1][2][15-1] = true;   badChamberRun[0][1][1-1][2][15-1][0] = 357078; badChamberRun[0][1][1-1][2][15-1][1] = lastRun; badChamberLCS[0][1][1-1][2][15-1][0] = -2.0; badChamberLCS[0][1][1-1][2][15-1][1] = 18.0;// ME+12/15 DCFEB 1 all runs good around 359000 and before except for 357078 to 357734

    //ME+12-20 a few zero runs

    badChamber[0][1][1-1][2][21-1] = true;   badChamberRun[0][1][1-1][2][21-1][0] = firstRun; badChamberRun[0][1][1-1][2][21-1][1] = lastRun; badChamberLCS[0][1][1-1][2][21-1][0] = 14.0; badChamberLCS[0][1][1-1][2][21-1][1] = 66.0;// ME+12/21 DCFEB 2,4 all runs, breifly brought back around 359200
                                                                                                                                                                                                                                       //ME+12=24 a few low eff runs

    badChamber[0][1][1-1][2][31-1] = true;   badChamberRun[0][1][1-1][2][31-1][0] = firstRun; badChamberRun[0][1][1-1][2][31-1][1] = lastRun; badChamberLCS[0][1][1-1][2][31-1][0] = 62.0; badChamberLCS[0][1][1-1][2][31-1][1] = 82.0;// ME+12/31 all runs

    badChamber[0][1][1-1][2][34-1] = true;   badChamberRun[0][1][1-1][2][34-1][0] = 359570; badChamberRun[0][1][1-1][2][34-1][1] = 360142;// ME+12/34 for 359570 to 360142


    // ME+11A/B
    // ME+11A/B

    // ME+11A.B-1 gen low LCT 83%
    // ME+11A/B-13 357480 357482 very low eff
    // ME+11A/B-21 a few low stats run ranges
    // ME+11A/B-28 a few low stats run ranges

    if (badRunRangesTrack) badChamber[0][1][1-1][1][27-1] = true;   badChamberRun[0][1][1-1][1][27-1][0] = 357696; badChamberRun[0][1][1-1][1][27-1][1] = 357720;// ME+11A/27
    if (badRunRangesTrack) badChamber[0][1][1-1][0][27-1] = true;   badChamberRun[0][1][1-1][0][27-1][0] = 357696; badChamberRun[0][1][1-1][0][27-1][1] = 357720;// ME+11B/27


    // ME-11A
    badChamber[0][0][1-1][0][19-1] = true;  badChamberRun[0][0][1-1][0][19-1][0] = firstRun; badChamberRun[0][0][1-1][0][19-1][1] = lastRun; badChamberLCS[0][0][1-1][0][19-1][0] = 30.0; badChamberLCS[0][0][1-1][0][19-1][1] = 50.0;// ME-11A/19 all runs

    badChamber[0][0][1-1][0][20-1] = true;  badChamberRun[0][0][1-1][0][20-1][0] = firstRun; badChamberRun[0][0][1-1][0][20-1][1] = lastRun; badChamberLCS[0][0][1-1][0][20-1][0] = -2.0; badChamberLCS[0][0][1-1][0][20-1][1] = 18.0;// ME-11A/20 all runs good around 359000



    // ME-11A/B
    // also less inefficinecy earlier
    if (badRunRangesTrack) badChamber[0][0][1-1][1][4-1] = true;   badChamberRun[0][0][1-1][1][4-1][0] = 359602; badChamberRun[0][0][1-1][1][4-1][1] = 359814;// ME-11A/4 359602 to 359814
    if (badRunRangesTrack) badChamber[0][0][1-1][0][4-1] = true;   badChamberRun[0][0][1-1][0][4-1][0] = 359602; badChamberRun[0][0][1-1][0][4-1][1] = 359814;// ME-11B/4 359602 to 359814
    if (badRunRangesTrack) badChamber[0][0][1-1][0][33-1] = true;   badChamberRun[0][0][1-1][0][33-1][0] = 356722; badChamberRun[0][0][1-1][0][33-1][1] = 357112;// ME-11B/33

    //if (badRunRangesTrack) badChamber[0][0][1-1][1][4-1] = true;   badChamberRun[0][0][1-1][1][4-1][0] = 361000.0; badChamberRun[0][0][1-1][1][4-1][1] = 361400.0;// ME-11A/4 transient E and then F 90% don't remove
    //if (badRunRangesTrack) badChamber[0][0][1-1][0][4-1] = true;   badChamberRun[0][0][1-1][0][4-1][0] = 361000.0; badChamberRun[0][0][1-1][0][4-1][1] = 361400.0;// ME-11B/4 transient E and then F 90% dont remove


    // three ranges 355134-355560, 356434-356490, 357406-357734
    if (badRunRangesTrack) badChamber[0][0][1-1][1][12-1] = true;   badChamberRun[0][0][1-1][1][12-1][0] = 355134; badChamberRun[0][0][1-1][1][12-1][1] = 357734;// ME-11A/12 transient B
    if (badRunRangesTrack) badChamber[0][0][1-1][0][12-1] = true;   badChamberRun[0][0][1-1][0][12-1][0] = 355134; badChamberRun[0][0][1-1][0][12-1][1] = 357734;// ME-11B/12 transient B

    if (badRunRangesTrack) badChamber[0][0][1-1][1][25-1] = true;   badChamberRun[0][0][1-1][1][25-1][0] = 357330; badChamberRun[0][0][1-1][1][25-1][1] = 357334;// ME-11A/25 transient B
    if (badRunRangesTrack) badChamber[0][0][1-1][0][25-1] = true;   badChamberRun[0][0][1-1][0][25-1][0] = 357330; badChamberRun[0][0][1-1][0][25-1][1] = 357334;// ME-11B/25 transient B

    if (badRunRangesTrack) badChamber[0][0][1-1][1][29-1] = true;   badChamberRun[0][0][1-1][1][29-1][0] = 360762; badChamberRun[0][0][1-1][1][29-1][1] = 361362;// ME-11A/29 transient F ?????? HV layer 3
    if (badRunRangesTrack) badChamber[0][0][1-1][0][29-1] = true;   badChamberRun[0][0][1-1][0][29-1][0] = 360762; badChamberRun[0][0][1-1][0][29-1][1] = 361362;// ME-11B/29 transient F ?????? HV layer 3


    // ME-12
    if (badRunRangesTrack) badChamber[0][0][1-1][2][7-1] = true;   badChamberRun[0][0][1-1][2][7-1][0] = 356322.0; badChamberRun[0][0][1-1][2][7-1][1] = 357734.0;// ME-12/7
    if (badRunRangesTrack) badChamber[0][0][1-1][2][22-1] = true;   badChamberRun[0][0][1-1][2][22-1][0] = 355680.0; badChamberRun[0][0][1-1][2][22-1][1] = 357614;// ME-12/22 two ranges 355680-355770, 357328-357614

    badChamber[0][0][1-1][2][27-1] = true;  badChamberRun[0][0][1-1][2][27-1][0] = firstRun; badChamberRun[0][0][1-1][2][27-1][1] = lastRun; badChamberLCS[0][0][1-1][2][27-1][0] = -2.0; badChamberLCS[0][0][1-1][2][27-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs good around 359000
    badChamber[0][0][1-1][2][33-1] = true;  badChamberRun[0][0][1-1][2][33-1][0] = firstRun; badChamberRun[0][0][1-1][2][33-1][1] = lastRun; badChamberLCS[0][0][1-1][2][33-1][0] = -2.0; badChamberLCS[0][0][1-1][2][33-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs good around 359000


    // ME-13
    if (badRunRangesTrack&&badRunRangesTrack2) badChamber[0][0][1-1][3][25-1] = true;   badChamberRun[0][0][1-1][3][25-1][0] = 355680; badChamberRun[0][0][1-1][3][25-1][1] = 357614;// ME-13/25 transient B

    //ME-13 30 low in 3 our of 4 (D)CFEBs for LCTs 83%

    // ME-21

    badChamber[0][0][2-1][1][15-1] = true;   badChamberRun[0][0][2-1][1][15-1][0] = firstRun; badChamberRun[0][0][2-1][1][15-1][1] = lastRun; badChamberLCS[0][0][2-1][1][15-1][0] = -2.0; badChamberLCS[0][0][2-1][1][15-1][1] = 18.0;// ME-21/15 also 0% 355988-356078

    //worst ME-21 chamber Seg and LCT also a few zero eff runs
    //badChamber[0][0][2-1][1][18-1] = true;   badChamberRun[0][0][2-1][1][18-1][0] = firstRun; badChamberRun[0][0][2-1][1][18-1][1] = lastRun;// ME-21/18


    // ME-22
    // ME-22/1 86% LCT only no dependence
    badChamber[0][0][2-1][2][3-1] = true;   badChamberRun[0][0][2-1][2][3-1][0] = firstRun; badChamberRun[0][0][2-1][2][3-1][1] = lastRun; badChamberLCS[0][0][2-1][2][3-1][0] = 14.0; badChamberLCS[0][0][2-1][2][3-1][1] = 34.0;// ME-22/3 DCFEB 2 all runs, gen low LCT 86%
    badChamber[0][0][2-1][2][27-1] = true;   badChamberRun[0][0][2-1][2][27-1][0] = firstRun; badChamberRun[0][0][2-1][2][27-1][1] = lastRun; badChamberLCS[0][0][2-1][2][27-1][0] = 62.0; badChamberLCS[0][0][2-1][2][27-1][1] = 82.0;// ME-22/27 DCFEB 5 all runs good around 359000
                                                                                                                                                                                                                                       // ME-22/15 DCFEB 2 80% eff

                                                                                                                                                                                                                                       //ME-31
    badChamber[0][0][3-1][1][3-1] = true;   badChamberRun[0][0][3-1][1][3-1][0] = firstRun; badChamberRun[0][0][3-1][1][3-1][1] = 359000; badChamberLCS[0][0][3-1][1][3-1][0] = -2.0; badChamberLCS[0][0][3-1][1][3-1][1] = 18.0;// ME-31/3 B-D also 0% 356048-356078
    if (badRunRangesTrack) badChamber[0][0][3-1][1][5-1] = true;   badChamberRun[0][0][3-1][1][5-1][0] = 355862; badChamberRun[0][0][3-1][1][5-1][1] = 356824;// ME-31/5 transient B
                                                                                                                                                              //ME-31/9 one run 362440 0.296893 and other single runs
    if (badRunRangesTrack) badChamber[0][0][3-1][1][14-1] = true;   badChamberRun[0][0][3-1][1][14-1][0] = 357478; badChamberRun[0][0][3-1][1][14-1][1] = 357734;// ME-31/14 transient B
    if (badRunRangesTrack) badChamber[0][0][3-1][1][18-1] = true;   badChamberRun[0][0][3-1][1][18-1][0] = 355680; badChamberRun[0][0][3-1][1][18-1][1] = 357734;// ME-31/18 B-D

    // ME-32
    badChamber[0][0][3-1][2][19-1] = true;   badChamberRun[0][0][3-1][2][19-1][0] = firstRun; badChamberRun[0][0][3-1][2][19-1][1] = lastRun; badChamberLCS[0][0][3-1][2][19-1][0] = 46.0; badChamberLCS[0][0][3-1][2][19-1][1] = 66.0;// ME-32/19 DCFEB 3 all runs, also poor efficiency runs 361188-362760 ??????
    badChamber[0][0][3-1][2][24-1] = true;   badChamberRun[0][0][3-1][2][24-1][0] = 360486; badChamberRun[0][0][3-1][2][24-1][1] = 361110; // ME-32/24 and some other single runs
                                                                                                                                           // ME-31/30 LCT 1-4 87%


                                                                                                                                           // ME-41
    if (badRunRangesTrack&&badRunRangesTrack) badChamber[0][0][4-1][1][3-1] = true;   badChamberRun[0][0][4-1][1][3-1][0] = 357330; badChamberRun[0][0][4-1][1][3-1][1] = 357734;// ME-41/3 B-D to area of bad runs 355408-356048, 357330-357734
    if (badRunRangesTrack) badChamber[0][0][4-1][1][12-1] = true;   badChamberRun[0][0][4-1][1][12-1][0] = 355862; badChamberRun[0][0][4-1][1][12-1][1] = 357734;// ME-41/12 transient B several area of zero eff 355862-355872, 356446-357734
    badChamber[0][0][4-1][1][17-1] = true;   badChamberRun[0][0][4-1][1][17-1][0] = firstRun; badChamberRun[0][0][4-1][1][17-1][1] = lastRun; badChamberLCS[0][0][4-1][1][17-1][0] = 46.0; badChamberLCS[0][0][4-1][1][17-1][1] = 66.0;// ME-41/17 DCFEB 4 all reun


    // ME-41/15 80% efficiency issues transient in period F
    if (badRunRangesTrack) badChamber[0][0][4-1][1][15-1] = true;   badChamberRun[0][0][4-1][1][15-1][0] = 360116; badChamberRun[0][0][4-1][1][15-1][1] = 361476;// ME-41/15 transient F


    // There are some other transient DCFEB problems I might want to track down


    // ME-42
    // ME-42/19 53% LCT only
    badChamber[0][0][4-1][2][27-1] = true;   badChamberRun[0][0][4-1][2][27-1][0] = firstRun; badChamberRun[0][0][4-1][2][27-1][1] = lastRun ; badChamberLCS[0][0][4-1][2][27-1][0] = 30.0; badChamberLCS[0][0][4-1][2][27-1][1] = 50.0;// ME-42/27 DCFEB 3  all runs good around 359200
    badChamber[0][0][4-1][2][30-1] = true;   badChamberRun[0][0][4-1][2][30-1][0] = 361366; badChamberRun[0][0][4-1][2][30-1][1] = lastRun ; // ME-42/30  30% efficiency problem at end of F

  }


  // Dead chambers

  if (oldBadChambersTrack) {
    badChamber[0][0][2-1][1][3-1] = true;  badChamberRun[0][0][2-1][1][3-1][0] = 316000; badChamberRun[0][0][2-1][1][3-1][1] = 325273; //ME-21/3 no data

    badChamber[0][0][4-1][2][21-1] = true;  badChamberRun[0][0][4-1][2][21-1][0] = 316000; badChamberRun[0][0][4-1][2][21-1][1] = 325273; // ME-42/21 no data



    badChamber[0][0][4-1][2][14-1] = true;  badChamberRun[0][0][4-1][2][14-1][0] = 316000; badChamberRun[0][0][4-1][2][14-1][1] = 325273; badChamberLCS[0][0][4-1][2][14-1][0] = 14.5; badChamberLCS[0][0][4-1][2][14-1][1] = 34.5;// ME-42/14 DCFEB 2


    //badChamber[0][0][1-1][0][9-1] = true;  badChamberRun[0][0][1-1][0][9-1][0] = 322599; badChamberRun[0][0][1-1][0][9-1][1] = 322633; // ME-11A/9 322599-322633 !!!!! me-1/1/09	2018-08-19	DCFEB1	opt link with ODMB time correct
    // ME-11A/10 bad in first run section
    badChamber[0][0][1-1][0][11-1] = true;  badChamberRun[0][0][1-1][0][11-1][0] = 316000; badChamberRun[0][0][1-1][0][11-1][1] = 325172; badChamberLCS[0][0][1-1][0][11-1][0] = 31.0; badChamberLCS[0][0][1-1][0][11-1][1] = 50.0;// ME-11A/11
                                                                                                                                                                                                                                   //badChamber[0][0][1-1][0][12-1] = true;   badChamberRun[0][0][1-1][0][12-1][0] = 322355; badChamberRun[0][0][1-1][0][12-1][1] = 322492;// ME-11B/12 322355-322492 !!!!! General low efficiencies more toward end, Nothing
    badChamber[0][0][1-1][0][25-1] = true;  badChamberRun[0][0][1-1][0][25-1][0] = 321067; badChamberRun[0][0][1-1][0][25-1][1] = 325172; badChamberLCS[0][0][1-1][0][25-1][0] = 0.0; badChamberLCS[0][0][1-1][0][25-1][1] = 16.5;// ME-11A/11 okay before 321067
                                                                                                                                                                                                                                  // ME-11A/26 bad at 322057 !!!!! Some low efficiencies me-1/1/26	2018-07-21	DCFEB3	opt link with ODMB, me-1/1/26	2018-12-01	DCFEB3	OTMB time note correct
                                                                                                                                                                                                                                  // badChamber[0][0][1-1][0][29-1] = true;  badChamberRun[0][0][1-1][0][29-1][0] = 322605; badChamberRun[0][0][1-1][0][29-1][1] = 322605;// ME-11A/29 322605 !!!!! Some low efficiencies Nothing

    badChamber[0][0][1-1][1][5-1] = true;   badChamberRun[0][0][1-1][1][5-1][0] = 316000; badChamberRun[0][0][1-1][1][5-1][1] = 325172; badChamberLCS[0][0][1-1][1][5-1][0] = 0.0; badChamberLCS[0][0][1-1][1][5-1][1] = 16.5;// ME-11B/5
                                                                                                                                                                                                                              // ME-11B/10 bad in first run section
                                                                                                                                                                                                                              // badChamber[0][0][1-1][1][12-1] = true;   badChamberRun[0][0][1-1][1][12-1][0] = 322355; badChamberRun[0][0][1-1][1][12-1][1] = 322492;// ME-11B/12 322355-322492 !!!!! Some low efficiecies in middle Nothing
                                                                                                                                                                                                                              // ME-11B/26 70% one run at 321232 !!!!! me-1/1/26	2018-07-21	DCFEB3	opt link with ODMB time correct
                                                                                                                                                                                                                              // badChamber[0][0][1-1][1][29-1] = true;   badChamberRun[0][0][1-1][1][29-1][0] = 322605; badChamberRun[0][0][1-1][1][29-1][1] = 322605;// ME-11B/29 322605 !!!!! Some low efficiences in middle Nothing

    badChamber[0][0][1-1][2][6-1] = true;   badChamberRun[0][0][1-1][2][6-1][0] = 323423; badChamberRun[0][0][1-1][2][6-1][1] = 323526; badChamberLCS[0][0][1-1][2][6-1][0] = 46.5; badChamberLCS[0][0][1-1][2][6-1][1] = 62.5;// ME-12/6 323423-323526
    badChamber[0][0][1-1][2][21-1] = true;   badChamberRun[0][0][1-1][2][21-1][0] = 316000; badChamberRun[0][0][1-1][2][21-1][1] = 325172; badChamberLCS[0][0][1-1][2][21-1][0] = 32.5; badChamberLCS[0][0][1-1][2][21-1][1] = 40.5;// ME-12/21 316000-325172
    badChamber[0][0][1-1][2][33-1] = true;   badChamberRun[0][0][1-1][2][33-1][0] = 316000; badChamberRun[0][0][1-1][2][33-1][1] = 325172; badChamberLCS[0][0][1-1][2][33-1][0] = 0.0; badChamberLCS[0][0][1-1][2][33-1][1] = 16.5;// ME-12/33
    badChamber[0][0][1-1][2][36-1] = true;   badChamberRun[0][0][1-1][2][36-1][0] = 321700; badChamberRun[0][0][1-1][2][36-1][1] = 325172; badChamberLCS[0][0][1-1][2][36-1][0] = 65.5; badChamberLCS[0][0][1-1][2][36-1][1] = 40.5;// ME-12/36 321700-325172


    badChamber[0][0][1-1][3][8-1] = true;   badChamberRun[0][0][1-1][3][8-1][0] = 316000; badChamberRun[0][0][1-1][3][8-1][1] = 321314; badChamberLCS[0][0][1-1][3][8-1][0] = 48.5; badChamberLCS[0][0][1-1][3][8-1][1] = 62.5;// ME-13/8 323423-323526

    badChamber[0][0][1-1][3][25-1] = true;   badChamberRun[0][0][1-1][3][25-1][0] = 316000; badChamberRun[0][0][1-1][3][25-1][1] = 321070; badChamberLCS[0][0][1-1][3][25-1][0] = 30.; badChamberLCS[0][0][1-1][3][25-1][1] = 50.5;// ME-13/25 316000-


    //ME13/35 bad in first run section


    badChamber[0][1][1-1][0][7-1] = true;  badChamberRun[0][1][1-1][0][7-1][0] = 318800; badChamberRun[0][1][1-1][0][7-1][1] = 325172; badChamberLCS[0][1][1-1][0][7-1][0] = 0.0; badChamberLCS[0][1][1-1][0][7-1][1] = 16.5;// ME+11A/7
    badChamber[0][1][1-1][0][20-1] = true; badChamberRun[0][1][1-1][0][20-1][0] = 318800; badChamberRun[0][1][1-1][0][20-1][1] = 325172; badChamberLCS[0][1][1-1][0][20-1][0] = 32.5; badChamberLCS[0][1][1-1][0][20-1][1] = 50.0; // ME+11A/20
                                                                                                                                                                                                                                   // badChamber[0][1][1-1][0][21-1] = true; badChamberRun[0][1][1-1][0][21-1][0] = 323755; badChamberRun[0][1][1-1][0][21-1][1] = 324022; // ME+11A/21 323755-324022 40% !!!!! Some low efficiencies in middle me+1/1/21	2018-08-17	DCFEB3	opt link with OTMB time not correct
    badChamber[0][1][1-1][0][29-1] = true; badChamberRun[0][1][1-1][0][29-1][0] = 318800; badChamberRun[0][1][1-1][0][29-1][1] = 325172; badChamberLCS[0][1][1-1][0][29-1][0] = 14.5; badChamberLCS[0][1][1-1][0][29-1][1] = 32.5;// ME+11A/29


    //ME+11B/18 run 319077 !!!!! A vew low efficiences in middle  me+1/1/18	2018-10-19	DCFEB7	ODMB time not correct
    // badChamber[0][1][1-1][1][21-1] = true;  badChamberRun[0][1][1-1][1][21-1][0] = 323755; badChamberRun[0][1][1-1][1][21-1][1] = 324022; // ME+11B/21 323755-324022 40% !!!!! Some low efficiencies in middle me+1/1/21	2018-08-17	DCFEB3	opt link with time approximately correct


    //ME+12/5 bad before 318800
    // badChamber[0][1][1-1][2][8-1] = true;   badChamberRun[0][1][1-1][2][8-1][0] = 321067; badChamberRun[0][1][1-1][2][8-1][1] = 321305;// ME+12/8 ** only 321067-321305 and 322013,322014 !!!!! A few low efficincies in the middle Nothing
    badChamber[0][1][1-1][2][13-1] = true;  badChamberRun[0][1][1-1][2][13-1][0] = 316000; badChamberRun[0][1][1-1][2][13-1][1] = 325172; badChamberLCS[0][1][1-1][2][13-1][0] = 62.5; badChamberLCS[0][1][1-1][2][13-1][1] = 80.0;// ME+12/13
    badChamber[0][1][1-1][2][20-1] = true;  badChamberRun[0][1][1-1][2][20-1][0] = 316000; badChamberRun[0][1][1-1][2][20-1][1] = 325172; badChamberLCS[0][1][1-1][2][20-1][0] = 30.5; badChamberLCS[0][1][1-1][2][20-1][1] = 50.5;// ME+12/20
    badChamber[0][1][1-1][2][21-1] = true;  badChamberRun[0][1][1-1][2][21-1][0] = 316000; badChamberRun[0][1][1-1][2][21-1][1] = 325172; badChamberLCS[0][1][1-1][3][21-1][0] = 14.5; badChamberLCS[0][1][1-1][2][21-1][1] = 66.5;// ME+12/21
                                                                                                                                                                                                                                   // badChamber[0][1][1-1][2][28-1] = true;  badChamberRun[0][1][1-1][2][28-1][0] = 320955; badChamberRun[0][1][1-1][2][28-1][1] = 320809; // ME+12/28 320804-320809 and 320955 !!!!! A few low efficiency in middle Nothing
    badChamber[0][1][1-1][2][31-1] = true;  badChamberRun[0][1][1-1][2][31-1][0] = 316000; badChamberRun[0][1][1-1][2][31-1][1] = 325172; badChamberLCS[0][1][1-1][2][31-1][0] = 62.5; badChamberLCS[0][1][1-1][2][31-1][1] = 80.0;// ME+12/31

    badChamber[0][1][1-1][3][11-1] = true;  badChamberRun[0][1][1-1][3][11-1][0] = 316000; badChamberRun[0][1][1-1][3][11-1][1] = 325172; badChamberLCS[0][1][1-1][3][11-1][0] = 30.5; badChamberLCS[0][1][1-1][3][11-1][1] = 50.5;// ME+13/11


    //  ME-21/3 no data

    badChamber[0][0][2-1][2][1-1] = true;   badChamberRun[0][0][2-1][2][1-1][0] = 318800; badChamberRun[0][0][2-1][2][1-1][1] = 325172; badChamberLCS[0][0][2-1][2][1-1][0] = 44.5; badChamberLCS[0][0][2-1][2][1-1][1] = 66.6;// ME-22/1
    badChamber[0][0][2-1][2][3-1] = true;   badChamberRun[0][0][2-1][2][3-1][0] = 316000; badChamberRun[0][0][2-1][2][3-1][1] = 325172; badChamberLCS[0][0][2-1][2][3-1][0] = 15.5; badChamberLCS[0][0][2-1][2][3-1][1] = 32.5; // ME-22/3


    badChamber[0][1][2-1][1][3-1] = true;   badChamberRun[0][1][2-1][1][3-1][0] = 316000; badChamberRun[0][1][2-1][1][3-1][1] = 325172; badChamberLCS[0][1][2-1][1][3-1][0] = 14.5; badChamberLCS[0][1][2-1][1][3-1][1] = 64.5;// ME+21/3

    badChamber[0][1][2-1][2][5-1] = true;   badChamberRun[0][1][2-1][2][5-1][0] = 316000; badChamberRun[0][1][2-1][2][5-1][1] = 325172; badChamberLCS[0][1][2-1][2][5-1][0] = 0.; badChamberLCS[0][1][2-1][2][5-1][1] = 18.5;// ME+22/5
    badChamber[0][1][2-1][2][15-1] = true;   badChamberRun[0][1][2-1][2][15-1][0] = 316000; badChamberRun[0][1][2-1][2][15-1][1] = 325172; badChamberLCS[0][1][2-1][2][15-1][0] = 62.5; badChamberLCS[0][1][2-1][2][15-1][1] = 80.0;// ME+22/15
    badChamber[0][1][2-1][2][19-1] = true;   badChamberRun[0][1][2-1][2][19-1][0] = 316000; badChamberRun[0][1][2-1][2][19-1][1] = 325172; badChamberLCS[0][1][2-1][2][19-1][0] = 62.5; badChamberLCS[0][1][2-1][2][19-1][1] = 80.0;// ME+22/19


    badChamber[0][0][3-1][1][9-1] = true;   badChamberRun[0][0][3-1][1][9-1][0] = 316000; badChamberRun[0][0][3-1][1][9-1][1] = 325172; badChamberLCS[0][0][3-1][1][9-1][0] = 0.0; badChamberLCS[0][0][3-1][1][9-1][1] = 66.5;// ME-31/9 ** two ranges
    badChamber[0][0][3-1][1][13-1] = true;  badChamberRun[0][0][3-1][1][13-1][0] = 316000; badChamberRun[0][0][3-1][1][13-1][1] = 325172; badChamberLCS[0][0][3-1][1][13-1][0] = 30.5; badChamberLCS[0][0][3-1][1][13-1][1] = 50.5;// ME-31/13


    badChamber[0][1][3-1][1][7-1] = true;   badChamberRun[0][1][3-1][1][7-1][0] = 316000; badChamberRun[0][1][3-1][1][7-1][1] = 325172; badChamberLCS[0][1][3-1][1][7-1][0] = 30.5; badChamberLCS[0][1][3-1][1][7-1][1] = 48.5;// ME+31/7
    badChamber[0][1][3-1][1][12-1] = true;   badChamberRun[0][1][3-1][1][12-1][0] = 316000; badChamberRun[0][1][3-1][1][12-1][1] = 325172; badChamberLCS[0][1][3-1][1][12-1][0] = 62.5; badChamberLCS[0][1][3-1][1][12-1][1] = 77.5;// ME+31/12




    badChamber[0][1][3-1][2][19-1] = true;   badChamberRun[0][1][3-1][2][19-1][0] = 316000; badChamberRun[0][1][3-1][2][19-1][1] = 325172; badChamberLCS[0][1][3-1][2][19-1][0] = 62.5; badChamberLCS[0][1][3-1][2][19-1][1] = 80.0;// ME+32/19 all bad 78%
    badChamber[0][1][3-1][2][29-1] = true;   badChamberRun[0][1][3-1][2][29-1][0] = 316000; badChamberRun[0][1][3-1][2][29-1][1] = 325172; badChamberLCS[0][1][3-1][2][29-1][0] = 46.5; badChamberLCS[0][1][3-1][2][29-1][1] = 64.5;// ME+32/29


    badChamber[0][0][4-1][1][1-1] = true;   badChamberRun[0][0][4-1][1][1-1][0] = 316000; badChamberRun[0][0][4-1][1][1-1][1] = 325172; badChamberLCS[0][0][4-1][1][1-1][0] = 30.5; badChamberLCS[0][0][4-1][1][1-1][1] = 48.5;// ME-41/1
    badChamber[0][0][4-1][1][11-1] = true;   badChamberRun[0][0][4-1][1][11-1][0] = 316000; badChamberRun[0][0][4-1][1][11-1][1] = 325172; badChamberLCS[0][0][4-1][1][11-1][0] = 62.5; badChamberLCS[0][0][4-1][1][11-1][1] = 80.0;// ME-41/11
    badChamber[0][0][4-1][1][15-1] = true;   badChamberRun[0][0][4-1][1][15-1][0] = 316000; badChamberRun[0][0][4-1][1][15-1][1] = 325172; badChamberLCS[0][0][4-1][1][15-1][0] = 62.5; badChamberLCS[0][1][4-1][1][15-1][1] = 80.0;// ME-41/15



    //badChamber[0][0][4-1][2][2-1] = true;   badChamberRun[0][0][4-1][2][2-1][0] = 323492; badChamberRun[0][0][4-1][2][2-1][1] = 323493;// ME-42/2 323492-323493 !!!!! A few runs in the middle Nothing
    badChamber[0][0][4-1][2][8-1] = true;   badChamberRun[0][0][4-1][2][8-1][0] = 316000; badChamberRun[0][0][4-1][2][8-1][1] = 325172; badChamberLCS[0][0][4-1][2][8-1][0] = 14.5; badChamberLCS[0][0][4-1][2][8-1][1] = 34.5;// ME-42/8
    badChamber[0][0][4-1][2][27-1] = true;   badChamberRun[0][0][4-1][2][27-1][0] = 316000; badChamberRun[0][0][4-1][2][27-1][1] = 324077; badChamberLCS[0][0][4-1][2][27-1][0] = 30.5; badChamberLCS[0][0][4-1][2][27-1][1] = 50.5; // ME-42/27 323693-324077
    badChamber[0][0][4-1][2][34-1] = true;   badChamberRun[0][0][4-1][2][34-1][0] = 316000; badChamberRun[0][0][4-1][2][34-1][1] = 325172; badChamberLCS[0][0][4-1][2][34-1][0] = 62.5; badChamberLCS[0][0][4-1][2][34-1][1] = 80.0;// ME-42/34
                                                                                                                                                                                                                                    // ME-42/21 do data

    badChamber[0][1][4-1][1][15-1] = true;   badChamberRun[0][1][4-1][1][15-1][0] = 316000; badChamberRun[0][1][4-1][1][15-1][1] = 325172; badChamberLCS[0][1][4-1][1][15-1][0] = 62.5; badChamberLCS[0][1][4-1][1][15-1][1] = 80.0;// ME+41/15

    badChamber[0][1][4-1][2][32-1] = true;   badChamberRun[0][1][4-1][2][32-1][0] = 316000; badChamberRun[0][1][4-1][2][32-1][1] = 325172; badChamberLCS[0][1][4-1][2][32-1][0] = 0.0; badChamberLCS[0][1][4-1][2][32-1][1] = 18.5;// ME+42/32


    // CFEB SCA memory saturation effect

    badChamber[0][0][2-1][1][5-1] = true;   badChamberRun[0][0][2-1][1][5-1][0] = 316000; badChamberRun[0][0][2-1][1][5-1][1] = 325172; //ME-21/5
                                                                                                                                        //badChamber[0][0][2-1][1][8-1] = true;   badChamberRun[0][0][2-1][1][8-1][0] = 323423; badChamberRun[0][0][2-1][1][8-1][1] = 325172;// ME-21/9 323423-325172 Low efficiencies more at beginning and end, CFEB issue
                                                                                                                                        // Expand to full range
    badChamber[0][0][2-1][1][8-1] = true;   badChamberRun[0][0][2-1][1][8-1][0] = 316000; badChamberRun[0][0][2-1][1][8-1][1] = 325172;//

    //badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 318800; badChamberRun[0][0][2-1][1][9-1][1] = 325172; badChamberLCS[0][0][2-1][1][9-1][0] = 45.5; badChamberLCS[0][0][2-1][1][9-1][1] = 64.5;// ME-21/9 also  Low efficiencies more at end, CFEB issue
    // expand to full range
    badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 316000; badChamberRun[0][0][2-1][1][9-1][1] = 325172;

    badChamber[0][0][2-1][1][10-1] = true;   badChamberRun[0][0][2-1][1][10-1][0] = 316000; badChamberRun[0][0][2-1][1][10-1][1] = 325172;// ME-21/10 323432-325172 !!!!! Low efficiencies more at end, CFEB issue
    badChamber[0][0][2-1][1][17-1] = true;  badChamberRun[0][0][2-1][1][17-1][0] = 316000; badChamberRun[0][0][2-1][1][17-1][1] = 325172;// ME-21/17 !!!!! Low efficiencies more at end, CFEB issue

    // ME-22/16 CFEB Issue
    badChamber[0][0][2-1][2][16-1] = true;   badChamberRun[0][0][2-1][2][16-1][0] = 316000; badChamberRun[0][0][2-1][2][16-1][1] = 325172;
    // ME-22/20 323423-325172 40-90% efficiency !!!!! Low efficiencies more at end, CFEB issue
    badChamber[0][0][2-1][2][20-1] = true;   badChamberRun[0][0][2-1][2][20-1][0] = 316000; badChamberRun[0][0][2-1][2][20-1][1] = 325172;

    badChamber[0][0][3-1][1][18-1] = true;  badChamberRun[0][0][3-1][1][18-1][0] = 316000; badChamberRun[0][0][3-1][1][18-1][1] = 325172; //  ME-31/18 323423-325172  !!!!! !!!!! Low efficiencies more at end, CFEB issue ????

    //badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172; badChamberLCS[0][0][4-1][2][1-1][0] = 32.5; badChamberLCS[0][0][4-1][2][1-1][1] = 48.5;// ME-42/1 remaining CFEB issue?
    // expand to full range
    badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172;

    // Overlapping bad individual CFEB and CFEB SCA memory saturation issue

    // badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172; badChamberLCS[0][0][4-1][2][1-1][0] = 32.5; badChamberLCS[0][0][4-1][2][1-1][1] = 48.5;// ME-42/1 remaining CFEB issue?

    // badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 316000; badChamberRun[0][0][2-1][1][9-1][1] = 325172; badChamberLCS[0][0][2-1][1][9-1][0] = 45.5; badChamberLCS[0][0][2-1][1][9-1][1] = 64.5;// ME-21/9 also  Low efficiencies more at end, CFEB issue


  }
  //Exclude and ME-21 ring
  /* badChamber[0][0][2-1][1][1-1] = true;  badChamberRun[0][0][2-1][1][1-1][0] = 316000; badChamberRun[0][0][2-1][1][1-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][2-1] = true;  badChamberRun[0][0][2-1][1][2-1][0] = 316000; badChamberRun[0][0][2-1][1][2-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][4-1] = true;  badChamberRun[0][0][2-1][1][4-1][0] = 316000; badChamberRun[0][0][2-1][1][4-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][6-1] = true;  badChamberRun[0][0][2-1][1][6-1][0] = 316000; badChamberRun[0][0][2-1][1][6-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][7-1] = true;  badChamberRun[0][0][2-1][1][7-1][0] = 316000; badChamberRun[0][0][2-1][1][7-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][11-1] = true;  badChamberRun[0][0][2-1][1][11-1][0] = 316000; badChamberRun[0][0][2-1][1][11-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][12-1] = true;  badChamberRun[0][0][2-1][1][12-1][0] = 316000; badChamberRun[0][0][2-1][1][12-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][13-1] = true;  badChamberRun[0][0][2-1][1][13-1][0] = 316000; badChamberRun[0][0][2-1][1][13-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][14-1] = true;  badChamberRun[0][0][2-1][1][14-1][0] = 316000; badChamberRun[0][0][2-1][1][14-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][15-1] = true;  badChamberRun[0][0][2-1][1][15-1][0] = 316000; badChamberRun[0][0][2-1][1][15-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][16-1] = true;  badChamberRun[0][0][2-1][1][16-1][0] = 316000; badChamberRun[0][0][2-1][1][16-1][1] = lastRun; */
  /* badChamber[0][0][2-1][1][18-1] = true;  badChamberRun[0][0][2-1][1][18-1][0] = 316000; badChamberRun[0][0][2-1][1][18-1][1] = lastRun; */


  /* badChamber[0][1][2-1][1][2-1] = true;  badChamberRun[0][1][2-1][1][2-1][0] = 316000; badChamberRun[0][1][2-1][1][2-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][3-1] = true;  badChamberRun[0][1][2-1][1][3-1][0] = 316000; badChamberRun[0][1][2-1][1][3-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][4-1] = true;  badChamberRun[0][1][2-1][1][4-1][0] = 316000; badChamberRun[0][1][2-1][1][4-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][5-1] = true;  badChamberRun[0][1][2-1][1][5-1][0] = 316000; badChamberRun[0][1][2-1][1][5-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][6-1] = true;  badChamberRun[0][1][2-1][1][6-1][0] = 316000; badChamberRun[0][1][2-1][1][6-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][7-1] = true;  badChamberRun[0][1][2-1][1][7-1][0] = 316000; badChamberRun[0][1][2-1][1][7-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][8-1] = true;  badChamberRun[0][1][2-1][1][8-1][0] = 316000; badChamberRun[0][1][2-1][1][8-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][9-1] = true;  badChamberRun[0][1][2-1][1][9-1][0] = 316000; badChamberRun[0][1][2-1][1][9-1][1] = lastRun; */
  /*  badChamber[0][1][2-1][1][10-1] = true;  badChamberRun[0][1][2-1][1][10-1][0] = 316000; badChamberRun[0][1][2-1][1][10-1][1] = lastRun; */

  /* badChamber[0][1][2-1][1][1-1] = true;  badChamberRun[0][1][2-1][1][1-1][0] = 316000; badChamberRun[0][1][2-1][1][1-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][11-1] = true;  badChamberRun[0][1][2-1][1][11-1][0] = 316000; badChamberRun[0][1][2-1][1][11-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][12-1] = true;  badChamberRun[0][1][2-1][1][12-1][0] = 316000; badChamberRun[0][1][2-1][1][12-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][13-1] = true;  badChamberRun[0][1][2-1][1][13-1][0] = 316000; badChamberRun[0][1][2-1][1][13-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][14-1] = true;  badChamberRun[0][1][2-1][1][14-1][0] = 316000; badChamberRun[0][1][2-1][1][14-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][15-1] = true;  badChamberRun[0][1][2-1][1][15-1][0] = 316000; badChamberRun[0][1][2-1][1][15-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][16-1] = true;  badChamberRun[0][1][2-1][1][16-1][0] = 316000; badChamberRun[0][1][2-1][1][16-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][17-1] = true;  badChamberRun[0][1][2-1][1][17-1][0] = 316000; badChamberRun[0][1][2-1][1][17-1][1] = lastRun; */
  /*   badChamber[0][1][2-1][1][18-1] = true;  badChamberRun[0][1][2-1][1][18-1][0] = 316000; badChamberRun[0][1][2-1][1][18-1][1] = lastRun; */

