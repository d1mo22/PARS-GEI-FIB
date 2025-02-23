--===============================================================================================
--================================ Create one table per class ===================================
DROP TABLE IF EXISTS workorders CASCADE;
DROP TABLE IF EXISTS technicallogbookorders;
DROP TABLE IF EXISTS forecastedorders;

CREATE TABLE workorders  AS (SELECT * FROM "AMOS".workorders);
CREATE TABLE technicallogbookorders AS (
	SELECT 
		workorderid,
		reporteurclass,
		reporteurid,
		reportingdate,
		due,
		"deferred",
		mel 
	FROM "AMOS".technicallogbookorders);
CREATE TABLE forecastedorders AS (
	SELECT 
		workorderid,
		deadline,
		planned,
		frequency,
		frequencyunits,
		forecastedmanhours
	FROM "AMOS".forecastedorders);

-- YOU SHOULD CREATE HERE THE INTEGRITY CONSTRAINTS
--////////////////////////////////////////////////////////////////////////////////////////////////
alter table workorders
	add primary key (workorderid);

alter table technicallogbookorders 
	add primary key (workorderid);

alter table forecastedorders 
	add primary key (workorderid);

alter table technicallogbookorders
	add foreign key (workorderid)
		references workorders (workorderid);

alter table forecastedorders
	add foreign key (workorderid)
		references workorders (workorderid);

--////////////////////////////////////////////////////////////////////////////////////////////////

ANALYZE workorders;
ANALYZE technicallogbookorders;
ANALYZE forecastedorders;

--------------------------------------------------------------------------------------------------
------------------------------------ All possible queries ----------------------------------------
-- Title: Only generic data
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT * FROM workorders;
-- Title: Only specific data from technicallogbookorders
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT * FROM technicallogbookorders;
-- Title: Only specific data from forecastedorders 
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT * FROM forecastedorders;
-- Title: Both generic and specific data together for both kinds of slot
-- YOU SHOULD ADD HERE THE CORRESPONDING QUERY
--////////////////////////////////////////////////////////////////////////////////////////////////
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) select *
from workorders w
	left outer join technicallogbookorders t on t.workorderid = w.workorderid
	left outer join forecastedorders f on f.workorderid = w.workorderid;



--////////////////////////////////////////////////////////////////////////////////////////////////
																									
--===============================================================================================
--===================== Create only one table for the superclass ================================
DROP TABLE IF EXISTS workorders CASCADE;

CREATE TABLE workorders AS (	
	SELECT w.workorderid, w.aircraftregistration,	w.executiondate, w.executionplace, w.workpackage,	w.kind, 
				t.reporteurclass,	t.reporteurid, t.reportingdate, t.due, t."deferred", t.mel, 
				f.deadline, f.planned, f.frequency, f.frequencyunits, f.forecastedmanhours				
 	FROM "AMOS".workorders w 
		LEFT OUTER JOIN "AMOS".technicallogbookorders t ON w.workorderid=t.workorderid 
		LEFT OUTER JOIN "AMOS".forecastedorders f ON w.workorderid=f.workorderid);

ALTER TABLE workorders ADD PRIMARY KEY (workorderid);

ANALYZE workorders;

--------------------------------------------------------------------------------------------------
------------------------------------ All possible queries ----------------------------------------
-- Title: Only generic data
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT w.workorderid, w.aircraftregistration,	w.executiondate, w.executionplace, w.workpackage,	w.kind FROM workorders w;

-- Title: Only specific data from technicallogbookorders
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT w.workorderid, w.reporteurclass,	w.reporteurid, w.reportingdate, w.due, w."deferred", w.mel 
																									FROM workorders w
																									WHERE kind='TechnicalLogBook';
-- Title: Only specific data from forecastedorders 
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT w.workorderid, w.deadline, w.planned, w.frequency, w.frequencyunits, w.forecastedmanhours 
																									FROM workorders w
																									WHERE kind='Forecast';
-- Title: Both generic and specific data for both kinds of slot
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT * FROM workorders w;

--===============================================================================================
--===================== Create one table for each subclass ================================
DROP TABLE IF EXISTS technicallogbookorders;
DROP TABLE IF EXISTS forecastedorders;

CREATE TABLE technicallogbookorders AS (SELECT * FROM "AMOS".technicallogbookorders);
CREATE TABLE forecastedorders AS (SELECT * FROM "AMOS".forecastedorders);

ALTER TABLE technicallogbookorders ADD PRIMARY KEY (workorderid);
ALTER TABLE forecastedorders ADD PRIMARY KEY (workorderid);

ANALYZE technicallogbookorders;
ANALYZE forecastedorders;

--------------------------------------------------------------------------------------------------
------------------------------------ All possible queries ----------------------------------------
-- Title: Only generic data
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT t.workorderid, t.aircraftregistration,	t.executiondate, t.executionplace, t.workpackage,	t.kind FROM technicallogbookorders t
																									UNION ALL
																									SELECT f.workorderid, f.aircraftregistration,	f.executiondate, f.executionplace, f.workpackage,	f.kind FROM forecastedorders f;
-- Title: Only specific data from technicallogbookorders
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT t.workorderid, t.reporteurclass, t.reporteurid, t.reportingdate, t.due, t."deferred", t.mel FROM technicallogbookorders t;
-- Title: Only specific data from forecastedorders 
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT f.workorderid, f.deadline, f.planned, f.frequency, f.frequencyunits, f.forecastedmanhours FROM forecastedorders f;
-- Title: Both generic and specific data for both kinds of slot
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) 
-- YOU SHOULD ADD HERE THE CORRESPONDING QUERY
--////////////////////////////////////////////////////////////////////////////////////////////////
SELECT workorderid, aircraftregistration, executiondate, executionplace, workpackage, kind,
	reporteurclass, reporteurid, reportingdate, due, "deferred", mel,
	NULL as deadline, NULL as planned, NULL as frequency, NULL as frequencyunits, NULL as forecastedmanhours
FROM technicallogbookorders
UNION ALL
SELECT workorderid, aircraftregistration, executiondate, executionplace, workpackage, kind,
	NULL as reporteurclass, NULL as reporteurid, NULL as reportingdate, NULL as due, NULL as "deferred", NULL as mel,
	deadline, planned, frequency, frequencyunits, forecastedmanhours
FROM forecastedorders;

--////////////////////////////////////////////////////////////////////////////////////////////////
																								

--===================== Create one table per class, with inherit ================================
DROP TABLE IF EXISTS workorders CASCADE;
DROP TABLE IF EXISTS technicallogbookorders;
DROP TABLE IF EXISTS forecastedorders;

CREATE TABLE workorders (
	workorderid int4 NOT NULL,
	aircraftregistration bpchar(6) NOT NULL,
	executiondate date,
	executionplace bpchar(3),
	workpackage int4,
	kind bpchar(20) NOT NULL
);
																								
CREATE TABLE technicallogbookorders (
	reporteurclass bpchar(5) NOT NULL,
	reporteurid int2 NOT NULL,
	reportingdate date NOT NULL,
	due date,
	"deferred" bool,
	mel bpchar(1)
)
INHERITS (workorders);
INSERT INTO technicallogbookorders SELECT * FROM "AMOS".technicallogbookorders; 
	
CREATE TABLE forecastedorders (
	deadline date NOT NULL,
	planned date NOT NULL,
	frequency int2 NOT NULL,
	frequencyunits bpchar(10) NOT NULL,
	forecastedmanhours int2 NOT NULL
)
INHERITS (workorders);
INSERT INTO forecastedorders SELECT * FROM "AMOS".forecastedorders;

ALTER TABLE workorders ADD PRIMARY KEY (workorderid);
ALTER TABLE technicallogbookorders ADD PRIMARY KEY (workorderid);
ALTER TABLE forecastedorders ADD PRIMARY KEY (workorderid);

ANALYZE workorders;
ANALYZE technicallogbookorders;
ANALYZE forecastedorders;

--------------------------------------------------------------------------------------------------
------------------------------------ All possible queries ----------------------------------------
-- Title: Only generic data
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT * FROM workorders;
-- Title: Only specific data from technicallogbookorders
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT t.workorderid, t.reporteurclass, t.reporteurid, t.reportingdate, t.due, t."deferred", t.mel FROM technicallogbookorders t;;
-- Title: Only specific data from forecastedorders 
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) SELECT f.workorderid, f.deadline, f.planned, f.frequency, f.frequencyunits, f.forecastedmanhours FROM forecastedorders f;
-- Title: Both generic and specific data for both kinds of slot
EXPLAIN (ANALYZE TRUE, COSTS FALSE, SUMMARY true) 
-- YOU SHOULD ADD HERE THE CORRESPONDING QUERY
--////////////////////////////////////////////////////////////////////////////////////////////////

SELECT workorderid, aircraftregistration, executiondate, executionplace, workpackage, kind,
	reporteurclass, reporteurid, reportingdate, due, "deferred", mel,
	NULL as deadline, NULL as planned, NULL as frequency, NULL as frequencyunits, NULL as forecastedmanhours
FROM technicallogbookorders
UNION ALL
SELECT workorderid, aircraftregistration, executiondate, executionplace, workpackage, kind,
	NULL as reporteurclass, NULL as reporteurid, NULL as reportingdate, NULL as due, NULL as "deferred", NULL as mel,
	deadline, planned, frequency, frequencyunits, forecastedmanhours
FROM forecastedorders;


select count(*) from workorders;

--////////////////////////////////////////////////////////////////////////////////////////////////