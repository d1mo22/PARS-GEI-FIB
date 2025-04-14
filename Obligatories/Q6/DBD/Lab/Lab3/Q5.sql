CREATE VIEW nomVista AS
SELECT p.comarca, p.provincia, d.especialitatId, t.anyo, SUM(d.mossos) AS aggr
FROM destinacio d, data t, poblacio p
WHERE d.poblacioId=p.nom AND d.dataId=t.id
  AND t.anyo IN ('2003', '2004') AND p.comarca IN ('Barcelones','Segria', 'Noguera') AND d.especialitatID IN ('Transit', 'Investigacio')
GROUP BY CUBE(t.anyo, d.especialitatId), ROLLUP(p.provincia, p.comarca);