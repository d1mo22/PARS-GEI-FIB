
numBuses(8).
numDays(7).
maxDistance(1200).  % this is the maximal total distance for two consecutive days for a given bus

%
traject(mad,bcn,4,630).  % the traject mad-bcn has to take place at least 4 days per week, and is 630 km long.
traject(mad,val,1,360).
traject(mad,bil,1,400).
traject(mad,zar,3,320).
traject(mad,sev,1,450).
%
traject(bcn,mad,4,630).
traject(bcn,val,1,350).
traject(bcn,bil,2,610).
traject(bcn,zar,2,320).
traject(bcn,sev,1,800).
%
traject(val,mad,3,360).
traject(val,bcn,1,350).
traject(val,bil,1,610).
traject(val,zar,3,310).
traject(val,sev,1,700).
%
traject(bil,mad,4,400).
traject(bil,bcn,1,610).
traject(bil,val,1,610).
traject(bil,zar,1,300).
traject(bil,sev,1,900).
%
traject(zar,mad,1,320).
traject(zar,bcn,3,320).
traject(zar,val,1,310).
traject(zar,bil,1,300).
traject(zar,sev,1,800).

