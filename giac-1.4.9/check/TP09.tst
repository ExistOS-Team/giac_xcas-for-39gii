[],
"Warning: some commands like subs might change arguments order",
[],
"Done",
"Done",
"Done",
"Done",
"Done",
proc(a,n) 
  local A,B,C; 
  A:=1;  
  B:=a;  
  C:=n;  
  while C>0 do if irem(C,2)=1 then  
      A:=A*B; 
      C:=(C-1)/2; 
      B:=B*B else  
      C:=C/2; 
      B:=B*B 
    fi ; 
   od;;  
  A;  
 
end;,
128,
2361183241434822606848,
[1,1,1,0,0,0,1],
16,
2,
[8,15,22,29,36,43,50,57,64,71,78,85,92,99,106,113,120,127,134,141,148,155,162,169,176,183,190,197,204,211,218,225,232,239,246,253,260,267,274,281,288,295,302,309,316,323,330,337,344,351,358,365,372,379,386,393,400,407,414,421,428,435,442,449,456,463,470,477,484,491,498,505,512,519,526,533,540,547,554,561,568,575,582,589,596,603,610,617,624,631,638,645,652,659,666,673,680,687,694,701],
[pnt(pnt[line[0.0,50.05,50.05+0.0013986013986*I,0.0013986013986*I,0.0],56]),pnt(pnt[line[50.05,100.1,100.1+0.0013986013986*I,50.05+0.0013986013986*I,50.05],56]),pnt(pnt[line[100.1,150.15,150.15+0.0013986013986*I,100.1+0.0013986013986*I,100.1],56]),pnt(pnt[line[150.15,200.2,200.2+0.0013986013986*I,150.15+0.0013986013986*I,150.15],56]),pnt(pnt[line[200.2,250.25,250.25+0.0013986013986*I,200.2+0.0013986013986*I,200.2],56]),pnt(pnt[line[250.25,300.3,300.3+0.0013986013986*I,250.25+0.0013986013986*I,250.25],56]),pnt(pnt[line[300.3,350.35,350.35+0.0013986013986*I,300.3+0.0013986013986*I,300.3],56]),pnt(pnt[line[350.35,400.4,400.4+0.0015984015984*I,350.35+0.0015984015984*I,350.35],56]),pnt(pnt[line[400.4,450.45,450.45+0.0013986013986*I,400.4+0.0013986013986*I,400.4],56]),pnt(pnt[line[450.45,500.5,500.5+0.0013986013986*I,450.45+0.0013986013986*I,450.45],56]),pnt(pnt[line[500.5,550.55,550.55+0.0013986013986*I,500.5+0.0013986013986*I,500.5],56]),pnt(pnt[line[550.55,600.6,600.6+0.0013986013986*I,550.55+0.0013986013986*I,550.55],56]),pnt(pnt[line[600.6,650.65,650.65+0.0013986013986*I,600.6+0.0013986013986*I,600.6],56]),pnt(pnt[line[650.65,700.7,700.7+0.0013986013986*I,650.65+0.0013986013986*I,650.65],56]),pnt(pnt[line[700.7,750.75,750.75+0.0001998001998*I,700.7+0.0001998001998*I,700.7],56])],
100,
100,
[724,740,913,740,777,173,397,861,69,416,887,265,356,359,620,365,269,61,941,533,419,573,846,858,107,128,907,361,62,906,57,758,460,841,745,267,201,152,922,658,729,357,996,924,784,165,964,342,180,668,725,967,310,396,699,479,298,255,551,208,656,894,910,387,550,365,13,687,454,225,803,946,890,72,883,925,475,824,215,870,991,590,630,503,516,935,663,769,304,663,728,900,707,717,341,712,41,113,136,461],
[pnt(pnt[line[0.0,200.2,200.2+0.000749250749251*I,0.000749250749251*I,0.0],56]),pnt(pnt[line[200.2,400.4,400.4+0.0010989010989*I,200.2+0.0010989010989*I,200.2],56]),pnt(pnt[line[400.4,600.6,600.6+0.000699300699301*I,400.4+0.000699300699301*I,400.4],56]),pnt(pnt[line[600.6,800.8,800.8+0.00114885114885*I,600.6+0.00114885114885*I,600.6],56]),pnt(pnt[line[800.8,1001.0,1001.0+0.0012987012987*I,800.8+0.0012987012987*I,800.8],56])],
[pnt(pnt[line[0.0,50.05,50.05+0.0003996003996*I,0.0003996003996*I,0.0],56]),pnt(pnt[line[50.05,100.1,100.1+0.000999000999001*I,50.05+0.000999000999001*I,50.05],56]),pnt(pnt[line[100.1,150.15,150.15+0.000799200799201*I,100.1+0.000799200799201*I,100.1],56]),pnt(pnt[line[150.15,200.2,200.2+0.000799200799201*I,150.15+0.000799200799201*I,150.15],56]),pnt(pnt[line[200.2,250.25,250.25+0.000799200799201*I,200.2+0.000799200799201*I,200.2],56]),pnt(pnt[line[250.25,300.3,300.3+0.000999000999001*I,250.25+0.000999000999001*I,250.25],56]),pnt(pnt[line[300.3,350.35,350.35+0.000799200799201*I,300.3+0.000799200799201*I,300.3],56]),pnt(pnt[line[350.35,400.4,400.4+0.0017982017982*I,350.35+0.0017982017982*I,350.35],56]),pnt(pnt[line[400.4,450.45,450.45+0.0003996003996*I,400.4+0.0003996003996*I,400.4],56]),pnt(pnt[line[450.45,500.5,500.5+0.000999000999001*I,450.45+0.000999000999001*I,450.45],56]),pnt(pnt[line[500.5,550.55,550.55+0.000799200799201*I,500.5+0.000799200799201*I,500.5],56]),pnt(pnt[line[550.55,600.6,600.6+0.000599400599401*I,550.55+0.000599400599401*I,550.55],56]),pnt(pnt[line[600.6,650.65,650.65+0.0003996003996*I,600.6+0.0003996003996*I,600.6],56]),pnt(pnt[line[650.65,700.7,700.7+0.0013986013986*I,650.65+0.0013986013986*I,650.65],56]),pnt(pnt[line[700.7,750.75,750.75+0.001998001998*I,700.7+0.001998001998*I,700.7],56]),pnt(pnt[line[750.75,800.8,800.8+0.000799200799201*I,750.75+0.000799200799201*I,750.75],56]),pnt(pnt[line[800.8,850.85,850.85+0.000799200799201*I,800.8+0.000799200799201*I,800.8],56]),pnt(pnt[line[850.85,900.9,900.9+0.0015984015984*I,850.85+0.0015984015984*I,850.85],56]),pnt(pnt[line[900.9,950.95,950.95+0.001998001998*I,900.9+0.001998001998*I,900.9],56]),pnt(pnt[line[950.95,1001.0,1001.0+0.000799200799201*I,950.95+0.000799200799201*I,950.95],56])],
100,
97,
0.00599058971977,
1,
237,
54321,
10000,
[],
"Done",
[58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1,58,67,0,21,98,47,60,41,38,27,20,61,78,7,80,81,18,87,40,1],
[45,45,67,22,6,97,43,76,52,57,16,82,21,5,44,60,55,20,89,31,92,84,10,13,73,76,66,27,39,76,19,93,28,64,27,31,82,19,52,62,39,23,53,4,40,55,89,78,26,95,22,4,35,23,10,2,9,18,15,93,86,62,96,95,7,34,12,29,13,14,25,15,42,82,93,73,36,17,78,24,33,1,39,86,74,13,35,80,0,33,28,26,49,41,76,44,63,16,41,55,80,40,82,77,41,92,58,31,87,52,31,37,56,0,59,15,90,15,4,86,27,79,25,68,8,71,81,82,74,71,34,48,63,59,42,86,17,14,67,17,74,18,68,59,75,50,4,33,61,90,37,59,70,18,25,57,44,13,30,48,21,57,11,50,42,29,27,84,48,9,40,70,77,77,8,28,71,12,93,79,68,96,54,41,9,8,50,35,35,28,43,81,84,36,91,99,98,11,56,10,15,35,97,32,76,87,73,86,22,47,46,92,91,95,74,70,25,10,19,41,62,74,40,23,43,66,96,37,9,66,49,3,98,54,57,41,52,9,82,72,9,13,83,14,10,45,19,88,96,85,52,14,5,13,40,12,79,8,45,3,56,52,26,5,77,24,42,39,83,4,55,25,12,72,23,83,6,7,8,34,3,91,69,96,44,3,65,90,70,23,58,36,19,31,6,54,33,6,71,65,50,30,12,87,11,82,88,41,57,42,61,47,26,90,89,25,60,5,34,96,97,69,55,78,78,61,11,92,44,61,64,58,33,49,72,96,87,4,97,27,44,8,98,69,45,40,34,43,31,80,67,69,40,8,55,67,14,3,60,58,91,47,41,60,12,19,57,94,18,99,70,80,47,67,38,38,41,2,23,89,38,86,84,51,79,98,80,45,5,18,73,91,54,26,21,9,68,1,86,20,85,25,27,42,46,77,3,96,92,37,76,2,61,85,4,80,95,0,49,51,32,64,70,33,13,56,26,47,79,56,79,13,68,44,87,51,22,99,12,82,79,3,13,24,80,35,49,98,66,75,82,24,75,3,70,22,49,98,75,13,26,42,56,15,47,14,72,49,53,94,85,35,82,62,53,93,76,97,38,44,73,81,99,6,14,93,95,0,40,13,88,46,89,21,36,64,3,96,1,75],
[pnt(pnt[line[0.0,5.0,5.0+0.02*I,0.02*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.01*I,5.0+0.01*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0,10.0,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.01*I,15.0+0.01*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.02*I,20.0+0.02*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.01*I,25.0+0.01*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0,30.0,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.01*I,35.0+0.01*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.02*I,40.0+0.02*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.01*I,45.0+0.01*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0,50.0,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.01*I,55.0+0.01*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.02*I,60.0+0.02*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.01*I,65.0+0.01*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0,70.0,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.01*I,75.0+0.01*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.02*I,80.0+0.02*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.01*I,85.0+0.01*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0,90.0,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.01*I,95.0+0.01*I,95.0],56])],
[pnt(pnt[line[0.0,5.0,5.0+0.0104*I,0.0104*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.0104*I,5.0+0.0104*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0+0.0136*I,10.0+0.0136*I,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.0088*I,15.0+0.0088*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.0084*I,20.0+0.0084*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.0104*I,25.0+0.0104*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0+0.0084*I,30.0+0.0084*I,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.0092*I,35.0+0.0092*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.0144*I,40.0+0.0144*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.01*I,45.0+0.01*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0+0.008*I,50.0+0.008*I,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.0104*I,55.0+0.0104*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.0076*I,60.0+0.0076*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.008*I,65.0+0.008*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0+0.01*I,70.0+0.01*I,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.0112*I,75.0+0.0112*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.0108*I,80.0+0.0108*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.0096*I,85.0+0.0096*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0+0.0088*I,90.0+0.0088*I,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.0116*I,95.0+0.0116*I,95.0],56])],
[8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1,8,7,0,1],
[pnt(pnt[line[0.0,1.0,1.0+0.25*I,0.25*I,0.0],56]),pnt(pnt[line[1.0,2.0,2.0+0.25*I,1.0+0.25*I,1.0],56]),pnt(pnt[line[2.0,3.0,3.0,2.0,2.0],56]),pnt(pnt[line[3.0,4.0,4.0,3.0,3.0],56]),pnt(pnt[line[4.0,5.0,5.0,4.0,4.0],56]),pnt(pnt[line[5.0,6.0,6.0,5.0,5.0],56]),pnt(pnt[line[6.0,7.0,7.0,6.0,6.0],56]),pnt(pnt[line[7.0,8.0,8.0+0.25*I,7.0+0.25*I,7.0],56]),pnt(pnt[line[8.0,9.0,9.0+0.25*I,8.0+0.25*I,8.0],56])],
1,
237,
54321,
9999,
[],
"Done",
[63,65,70,22,31,78,27,68,10,93,68,17,72,91,56,79,62,81,60,61,25,92,6,69,94,96,51,99,19,5,84,71,78,99,33,82,66,19,12,63,94,18,7,4,7,47,18,56,94,39,62,9,95,88,52,41,10,79,91,35,24,57,93,19,27,40,76,66,41,68,67,82,59,41,89,23,87,47,82,23,8,3,87,11,49,37,72,27,89,66,98,56,58,6,76,72,19,91,7,89,30,65,70,22,31,78,27,68,10,93,68,17,72,91,56,79,62,81,60,61,25,92,6,69,94,96,51,99,19,5,84,71,78,99,33,82,66,19,12,63,94,18,7,4,7,47,18,56,94,39,62,9,95,88,52,41,10,79,91,35,24,57,93,19,27,40,76,66,41,68,67,82,59,41,89,23,87,47,82,23,8,3,87,11,49,37,72,27,89,66,98,56,58,6,76,72,19,91,7,89,30,65,70,22,31,78,27,68,10,93,68,17,72,91,56,79,62,81,60,61,25,92,6,69,94,96,51,99,19,5,84,71,78,99,33,82,66,19,12,63,94,18,7,4,7,47,18,56,94,39,62,9,95,88,52,41,10,79,91,35,24,57,93,19,27,40,76,66,41,68,67,82,59,41,89,23,87,47,82,23,8,3,87,11,49,37,72,27,89,66,98,56,58,6,76,72,19,91,7,89,30,65,70,22,31,78,27,68,10,93,68,17,72,91,56,79,62,81,60,61,25,92,6,69,94,96,51,99,19,5,84,71,78,99,33,82,66,19,12,63,94,18,7,4,7,47,18,56,94,39,62,9,95,88,52,41,10,79,91,35,24,57,93,19,27,40,76,66,41,68,67,82,59,41,89,23,87,47,82,23,8,3,87,11,49,37,72,27,89,66,98,56,58,6,76,72,19,91,7,89,30,65,70,22,31,78,27,68,10,93,68,17,72,91,56,79,62,81,60,61,25,92,6,69,94,96,51,99,19,5,84,71,78,99,33,82,66,19,12,63,94,18,7,4,7,47,18,56,94,39,62,9,95,88,52,41,10,79,91,35,24,57,93,19,27,40,76,66,41,68,67,82,59,41,89,23,87,47,82,23,8,3,87,11,49,37,72,27,89,66,98,56,58,6,76,72,19,91,7,89],
[45,58,44,38,2,90,60,28,41,84,73,7,42,68,76,89,25,15,90,17,17,31,9,90,38,72,36,96,32,73,57,52,36,60,99,86,21,77,39,15,47,6,8,56,26,22,69,40,56,39,79,15,19,71,80,28,77,17,59,43,18,66,21,41,6,29,11,30,10,10,74,41,55,19,43,46,0,49,68,55,34,21,27,49,83,32,15,69,61,12,43,67,56,54,56,96,68,5,44,88,12,58,44,38,2,90,60,28,41,84,73,7,42,68,76,89,25,15,90,17,17,31,9,90,38,72,36,96,32,73,57,52,36,60,99,86,21,77,39,15,47,6,8,56,26,22,69,40,56,39,79,15,19,71,80,28,77,17,59,43,18,66,21,41,6,29,11,30,10,10,74,41,55,19,43,46,0,49,68,55,34,21,27,49,83,32,15,69,61,12,43,67,56,54,56,96,68,5,44,88,12,58,44,38,2,90,60,28,41,84,73,7,42,68,76,89,25,15,90,17,17,31,9,90,38,72,36,96,32,73,57,52,36,60,99,86,21,77,39,15,47,6,8,56,26,22,69,40,56,39,79,15,19,71,80,28,77,17,59,43,18,66,21,41,6,29,11,30,10,10,74,41,55,19,43,46,0,49,68,55,34,21,27,49,83,32,15,69,61,12,43,67,56,54,56,96,68,5,44,88,12,58,44,38,2,90,60,28,41,84,73,7,42,68,76,89,25,15,90,17,17,31,9,90,38,72,36,96,32,73,57,52,36,60,99,86,21,77,39,15,47,6,8,56,26,22,69,40,56,39,79,15,19,71,80,28,77,17,59,43,18,66,21,41,6,29,11,30,10,10,74,41,55,19,43,46,0,49,68,55,34,21,27,49,83,32,15,69,61,12,43,67,56,54,56,96,68,5,44,88,12,58,44,38,2,90,60,28,41,84,73,7,42,68,76,89,25,15,90,17,17,31,9,90,38,72,36,96,32,73,57,52,36,60,99,86,21,77,39,15,47,6,8,56,26,22,69,40,56,39,79,15,19,71,80,28,77,17,59,43,18,66,21,41,6,29,11,30,10,10,74,41,55,19,43,46,0,49,68,55,34,21,27,49,83,32,15,69,61,12,43,67,56,54,56,96,68,5,44,88],
[pnt(pnt[line[0.0,5.0,5.0+0.004*I,0.004*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.016*I,5.0+0.016*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0+0.008*I,10.0+0.008*I,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.014*I,15.0+0.014*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.008*I,20.0+0.008*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.008*I,25.0+0.008*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0+0.0056*I,30.0+0.0056*I,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.006*I,35.0+0.006*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.008*I,40.0+0.008*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.006*I,45.0+0.006*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0+0.004*I,50.0+0.004*I,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.012*I,55.0+0.012*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.0104*I,60.0+0.0104*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.018*I,65.0+0.018*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0+0.01*I,70.0+0.01*I,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.012*I,75.0+0.012*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.01*I,80.0+0.01*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.012*I,85.0+0.012*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0+0.018*I,90.0+0.018*I,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.01*I,95.0+0.01*I,95.0],56])],
[pnt(pnt[line[0.0,5.0,5.0+0.004*I,0.004*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.012*I,5.0+0.012*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0+0.0096*I,10.0+0.0096*I,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.02*I,15.0+0.02*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.008*I,20.0+0.008*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.012*I,25.0+0.012*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0+0.01*I,30.0+0.01*I,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.012*I,35.0+0.012*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.02*I,40.0+0.02*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.0084*I,45.0+0.0084*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0+0.004*I,50.0+0.004*I,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.018*I,55.0+0.018*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.006*I,60.0+0.006*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.014*I,65.0+0.014*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0+0.01*I,70.0+0.01*I,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.008*I,75.0+0.008*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.006*I,80.0+0.006*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.006*I,85.0+0.006*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0+0.006*I,90.0+0.006*I,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.006*I,95.0+0.006*I,95.0],56])],
[3,5,0,2,1,8,7,8,0,3,8,7,2,1,6,9,2,1,0,1,5,2,6,9,4,6,1,9,9,5,4,1,8,9,3,2,6,9,2,3,4,8,7,4,7,7,8,6,4,9,2,9,5,8,2,1,0,9,1,5,4,7,3,9,7,0,6,6,1,8,7,2,9,1,9,3,7,7,2,3,8,3,7,1,9,7,2,7,9,6,8,6,8,6,6,2,9,1,7,9,0,5,0,2,1,8,7,8,0,3,8,7,2,1,6,9,2,1,0,1,5,2,6,9,4,6,1,9,9,5,4,1,8,9,3,2,6,9,2,3,4,8,7,4,7,7,8,6,4,9,2,9,5,8,2,1,0,9,1,5,4,7,3,9,7,0,6,6,1,8,7,2,9,1,9,3,7,7,2,3,8,3,7,1,9,7,2,7,9,6,8,6,8,6,6,2,9,1,7,9,0,5,0,2,1,8,7,8,0,3,8,7,2,1,6,9,2,1,0,1,5,2,6,9,4,6,1,9,9,5,4,1,8,9,3,2,6,9,2,3,4,8,7,4,7,7,8,6,4,9,2,9,5,8,2,1,0,9,1,5,4,7,3,9,7,0,6,6,1,8,7,2,9,1,9,3,7,7,2,3,8,3,7,1,9,7,2,7,9,6,8,6,8,6,6,2,9,1,7,9,0,5,0,2,1,8,7,8,0,3,8,7,2,1,6,9,2,1,0,1,5,2,6,9,4,6,1,9,9,5,4,1,8,9,3,2,6,9,2,3,4,8,7,4,7,7,8,6,4,9,2,9,5,8,2,1,0,9,1,5,4,7,3,9,7,0,6,6,1,8,7,2,9,1,9,3,7,7,2,3,8,3,7,1,9,7,2,7,9,6,8,6,8,6,6,2,9,1,7,9,0,5,0,2,1,8,7,8,0,3,8,7,2,1,6,9,2,1,0,1,5,2,6,9,4,6,1,9,9,5,4,1,8,9,3,2,6,9,2,3,4,8,7,4,7,7,8,6,4,9,2,9,5,8,2,1,0,9,1,5,4,7,3,9,7,0,6,6,1,8,7,2,9,1,9,3,7,7,2,3,8,3,7,1,9,7,2,7,9,6,8,6,8,6,6,2,9,1,7,9],
[pnt(pnt[line[0.0,1.0,1.0+0.058*I,0.058*I,0.0],56]),pnt(pnt[line[1.0,2.0,2.0+0.12*I,1.0+0.12*I,1.0],56]),pnt(pnt[line[2.0,3.0,3.0+0.12*I,2.0+0.12*I,2.0],56]),pnt(pnt[line[3.0,4.0,4.0+0.072*I,3.0+0.072*I,3.0],56]),pnt(pnt[line[4.0,5.0,5.0+0.06*I,4.0+0.06*I,4.0],56]),pnt(pnt[line[5.0,6.0,6.0+0.05*I,5.0+0.05*I,5.0],56]),pnt(pnt[line[6.0,7.0,7.0+0.11*I,6.0+0.11*I,6.0],56]),pnt(pnt[line[7.0,8.0,8.0+0.14*I,7.0+0.14*I,7.0],56]),pnt(pnt[line[8.0,9.0,9.0+0.11*I,8.0+0.11*I,8.0],56]),pnt(pnt[line[9.0,10.0,10.0+0.16*I,9.0+0.16*I,9.0],56])],
1,
237,
54321,
9973,
[],
"Done",
[93,94,44,95,62,27,20,98,29,1,58,77,43,76,26,47,76,89,96,18,57,31,49,96,8,78,54,68,32,45,76,15,35,10,43,69,1,95,29,47,57,90,83,78,28,29,40,32,38,36,36,62,1,93,79,17,96,95,16,85,61,10,61,21,46,87,92,14,9,76,11,78,50,96,45,72,58,75,63,19,40,91,14,72,82,7,98,19,22,81,96,6,13,24,81,70,67,21,38,43,91,68,73,69,67,69,17,40,17,26,64,95,45,50,18,70,23,72,28,64,84,33,84,72,43,6,10,26,62,45,15,89,96,3,30,32,82,85,46,41,8,28,95,14,20,31,23,99,43,91,83,0,95,34,80,52,50,63,66,1,99,1,34,30,8,50,50,46,59,18,46,61,10,76,48,72,54,3,76,46,22,51,42,54,79,2,84,96,75,41,37,8,52,27,49,20,40,13,81,50,22,27,10,46,52,20,94,14,41,10,93,25,1,82,9,78,76,35,10,58,96,27,62,40,82,94,36,23,42,32,12,24,44,76,63,14,7,69,27,92,94,7,28,58,47,89,24,92,25,79,15,31,38,56,96,10,28,57,29,27,12,96,82,81,89,81,61,77,39,4,39,74,85,22,24,27,27,53,35,73,34,38,95,97,71,21,44,65,8,2,86,76,32,27,66,97,69,41,87,79,52,13,96,62,21,68,54,70,54,29,88,11,8,89,94,53,27,71,87,18,26,1,62,49,57,49,44,87,48,80,26,23,44,54,96,36,67,49,15,65,64,95,3,23,92,3,12,37,91,18,44,96,53,89,59,94,99,99,84,0,47,28,10,26,92,99,67,23,18,0,77,24,62,86,81,7,76,52,44,41,76,67,86,94,42,45,59,66,25,31,36,34,12,98,32,84,50,76,28,97,6,50,18,85,50,98,95,75,19,70,30,12,80,37,93,10,74,56,42,67,14,98,64,18,59,23,79,83,70,56,9,45,24,64,51,11,67,38,30,99,45,41,13,61,90,1,73,19,96,42,4,93,75,72,82,22,25,18,89,92,31,16,59,64,45,74,50,5,50,81,18,46,91,64,1,82,94,51,50,68,26,23,86,81,22,3,78,11,52,11,4,32,34,6,76,15,50,37,69,36],
[46,96,81,97,21,82,95,67,99,40,52,39,95,22,53,1,93,25,96,86,24,83,42,41,16,65,76,33,48,27,67,47,49,72,78,82,95,22,98,2,31,46,89,91,55,81,62,73,68,94,68,89,42,27,81,81,33,14,97,33,88,2,43,8,95,29,42,44,34,45,19,85,29,54,5,39,83,6,48,1,27,55,31,44,71,12,12,29,81,45,30,2,34,55,71,9,49,48,1,72,56,68,65,64,17,43,27,1,77,83,30,25,11,65,10,63,82,85,15,75,19,59,43,62,49,91,84,30,35,9,90,67,77,71,24,19,35,56,54,86,79,37,3,83,2,67,40,4,30,75,83,66,28,24,28,88,80,74,79,75,69,77,45,19,31,30,92,26,32,89,37,46,21,58,8,59,36,28,5,13,43,15,30,73,20,85,48,50,54,55,12,84,25,9,47,30,21,30,4,87,38,27,25,9,92,31,58,51,97,93,68,25,45,40,45,59,50,7,91,93,82,59,29,83,63,10,44,86,36,99,47,42,82,35,42,75,1,98,97,59,83,92,24,14,9,94,94,39,31,70,67,2,93,35,94,11,82,97,31,80,20,25,13,28,90,43,55,59,48,44,10,13,9,85,96,15,73,56,78,63,89,75,57,15,39,81,43,67,21,54,81,97,76,81,57,46,6,34,21,41,75,91,0,72,2,69,3,85,10,49,57,99,97,14,82,54,3,21,3,64,96,20,99,18,38,10,37,41,94,96,48,13,88,61,68,32,34,83,85,79,72,6,96,65,45,57,97,24,35,78,23,14,99,96,69,81,16,81,28,98,33,98,0,68,65,9,18,81,48,94,82,14,28,45,42,18,38,55,38,79,15,89,53,43,86,81,0,84,63,75,41,73,73,20,30,49,88,75,48,17,15,23,29,78,82,49,21,60,81,38,41,59,93,35,49,10,44,76,38,74,89,27,93,97,38,15,63,3,54,43,96,79,25,42,77,64,79,77,33,57,25,92,5,63,60,17,86,55,59,93,45,47,34,2,90,27,13,93,87,30,92,81,31,51,16,53,15,28,10,39,5,75,76,21,87,21,29,59,86,0,6,32,3,61,33,39,19,45,64,77,69,51,40,31,25,66,64,72,42,89],
[pnt(pnt[line[0.0,5.0,5.0+0.0088*I,0.0088*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.0072*I,5.0+0.0072*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0+0.012*I,10.0+0.012*I,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.0096*I,15.0+0.0096*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.0112*I,20.0+0.0112*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.0132*I,25.0+0.0132*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0+0.0088*I,30.0+0.0088*I,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.008*I,35.0+0.008*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.0112*I,40.0+0.0112*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.0104*I,45.0+0.0104*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0+0.0124*I,50.0+0.0124*I,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.0064*I,55.0+0.0064*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.0088*I,60.0+0.0088*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.0088*I,65.0+0.0088*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0+0.0076*I,70.0+0.0076*I,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.012*I,75.0+0.012*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.0104*I,80.0+0.0104*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.008*I,85.0+0.008*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0+0.0104*I,90.0+0.0104*I,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.0148*I,95.0+0.0148*I,95.0],56])],
[pnt(pnt[line[0.0,5.0,5.0+0.0096*I,0.0096*I,0.0],56]),pnt(pnt[line[5.0,10.0,10.0+0.0072*I,5.0+0.0072*I,5.0],56]),pnt(pnt[line[10.0,15.0,15.0+0.0088*I,10.0+0.0088*I,10.0],56]),pnt(pnt[line[15.0,20.0,20.0+0.0088*I,15.0+0.0088*I,15.0],56]),pnt(pnt[line[20.0,25.0,25.0+0.0088*I,20.0+0.0088*I,20.0],56]),pnt(pnt[line[25.0,30.0,30.0+0.012*I,25.0+0.012*I,25.0],56]),pnt(pnt[line[30.0,35.0,35.0+0.0128*I,30.0+0.0128*I,30.0],56]),pnt(pnt[line[35.0,40.0,40.0+0.0096*I,35.0+0.0096*I,35.0],56]),pnt(pnt[line[40.0,45.0,45.0+0.012*I,40.0+0.012*I,40.0],56]),pnt(pnt[line[45.0,50.0,50.0+0.0128*I,45.0+0.0128*I,45.0],56]),pnt(pnt[line[50.0,55.0,55.0+0.006*I,50.0+0.006*I,50.0],56]),pnt(pnt[line[55.0,60.0,60.0+0.0104*I,55.0+0.0104*I,55.0],56]),pnt(pnt[line[60.0,65.0,65.0+0.0068*I,60.0+0.0068*I,60.0],56]),pnt(pnt[line[65.0,70.0,70.0+0.0092*I,65.0+0.0092*I,65.0],56]),pnt(pnt[line[70.0,75.0,75.0+0.0064*I,70.0+0.0064*I,70.0],56]),pnt(pnt[line[75.0,80.0,80.0+0.0116*I,75.0+0.0116*I,75.0],56]),pnt(pnt[line[80.0,85.0,85.0+0.0144*I,80.0+0.0144*I,80.0],56]),pnt(pnt[line[85.0,90.0,90.0+0.0104*I,85.0+0.0104*I,85.0],56]),pnt(pnt[line[90.0,95.0,95.0+0.0104*I,90.0+0.0104*I,90.0],56]),pnt(pnt[line[95.0,100.0,100.0+0.012*I,95.0+0.012*I,95.0],56])],
[3,4,4,5,2,7,0,8,9,1,8,7,3,6,6,7,6,9,6,8,7,1,9,6,8,8,4,8,2,5,6,5,5,0,3,9,1,5,9,7,7,0,3,8,8,9,0,2,8,6,6,2,1,3,9,7,6,5,6,5,1,0,1,1,6,7,2,4,9,6,1,8,0,6,5,2,8,5,3,9,0,1,4,2,2,7,8,9,2,1,6,6,3,4,1,0,7,1,8,3,1,8,3,9,7,9,7,0,7,6,4,5,5,0,8,0,3,2,8,4,4,3,4,2,3,6,0,6,2,5,5,9,6,3,0,2,2,5,6,1,8,8,5,4,0,1,3,9,3,1,3,0,5,4,0,2,0,3,6,1,9,1,4,0,8,0,0,6,9,8,6,1,0,6,8,2,4,3,6,6,2,1,2,4,9,2,4,6,5,1,7,8,2,7,9,0,0,3,1,0,2,7,0,6,2,0,4,4,1,0,3,5,1,2,9,8,6,5,0,8,6,7,2,0,2,4,6,3,2,2,2,4,4,6,3,4,7,9,7,2,4,7,8,8,7,9,4,2,5,9,5,1,8,6,6,0,8,7,9,7,2,6,2,1,9,1,1,7,9,4,9,4,5,2,4,7,7,3,5,3,4,8,5,7,1,1,4,5,8,2,6,6,2,7,6,7,9,1,7,9,2,3,6,2,1,8,4,0,4,9,8,1,8,9,4,3,7,1,7,8,6,1,2,9,7,9,4,7,8,0,6,3,4,4,6,6,7,9,5,5,4,5,3,3,2,3,2,7,1,8,4,6,3,9,9,4,9,9,4,0,7,8,0,6,2,9,7,3,8,0,7,4,2,6,1,7,6,2,4,1,6,7,6,4,2,5,9,6,5,1,6,4,2,8,2,4,0,6,8,7,6,0,8,5,0,8,5,5,9,0,0,2,0,7,3,0,4,6,2,7,4,8,4,8,9,3,9,3,0,6,9,5,4,4,1,1,7,8,0,9,5,1,3,1,0,1,3,9,6,2,4,3,5,2,2,2,5,8,9,2,1,6,9,4,5,4,0,5,0,1,8,6,1,4,1,2,4,1,0,8,6,3,6,1,2,3,8,1,2,1,4,2,4,6,6,5,0,7,9,6],
[pnt(pnt[line[0.0,1.0,1.0+0.098*I,0.098*I,0.0],56]),pnt(pnt[line[1.0,2.0,2.0+0.104*I,1.0+0.104*I,1.0],56]),pnt(pnt[line[2.0,3.0,3.0+0.114*I,2.0+0.114*I,2.0],56]),pnt(pnt[line[3.0,4.0,4.0+0.08*I,3.0+0.08*I,3.0],56]),pnt(pnt[line[4.0,5.0,5.0+0.112*I,4.0+0.112*I,4.0],56]),pnt(pnt[line[5.0,6.0,6.0+0.08*I,5.0+0.08*I,5.0],56]),pnt(pnt[line[6.0,7.0,7.0+0.126*I,6.0+0.126*I,6.0],56]),pnt(pnt[line[7.0,8.0,8.0+0.092*I,7.0+0.092*I,7.0],56]),pnt(pnt[line[8.0,9.0,9.0+0.098*I,8.0+0.098*I,8.0],56]),pnt(pnt[line[9.0,10.0,10.0+0.096*I,9.0+0.096*I,9.0],56])],
1,
237,
54321,
10,
[],
"Done",
[pnt(pnt[line[0.0,1.0,1.0+0.25*I,0.25*I,0.0],56]),pnt(pnt[line[1.0,2.0,2.0+0.25*I,1.0+0.25*I,1.0],56]),pnt(pnt[line[2.0,3.0,3.0,2.0,2.0],56]),pnt(pnt[line[3.0,4.0,4.0,3.0,3.0],56]),pnt(pnt[line[4.0,5.0,5.0,4.0,4.0],56]),pnt(pnt[line[5.0,6.0,6.0,5.0,5.0],56]),pnt(pnt[line[6.0,7.0,7.0,6.0,6.0],56]),pnt(pnt[line[7.0,8.0,8.0+0.25*I,7.0+0.25*I,7.0],56]),pnt(pnt[line[8.0,9.0,9.0+0.25*I,8.0+0.25*I,8.0],56])],
proc(a) 
  x:=1;  
  p:=1;  
  if (irem(a,5))<>0 then while x>0 do  
      p:=p+1; 
      x:=irem(a*x+1,125); 
     od; 
  fi ;  
  p;  
 
end;,
125,1,
100,100,50,1,125,20,100,50,1,125,100,100,50,1,125,100,20,50,1,125,100,100,10,1,125,100,100,50,1,125,20,100,50,1,125,100,100,50,1,125,100,20,50,1,125,100,100,10,1,125,100,100,50,1,125,4,100,50,1,125,100,100,50,1,125,100,4,50,1,125,100,100,10,1,125,100,100,50,1,125,20,100,50,1,125,100,100,50,1,125,100,20,50,1,125,100,100,10,1,125,100,100,50,1,125,20,100,50,1,125,100,100,50,1,125,100,20,50,1,125,100,100,2,
125
