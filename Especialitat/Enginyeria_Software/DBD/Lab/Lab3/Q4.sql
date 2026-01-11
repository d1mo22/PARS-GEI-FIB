CREATE VIEW nomVista AS
SELECT r.escala, p.provincia, SUM(d.mossos) AS aggr
FROM destinacio d, data t, poblacio p, rang r
WHERE d.poblacioId=p.nom AND d.dataId=t.id AND r.nom=d.rangId
  AND t.anyo='2009' AND p.provincia IN ('Barcelona','Tarragona','Lleida','Girona') AND r.escala IN ('Basica','Comand.') AND d.especialitatID='Antidisturbi'
GROUP BY ROLLUP(p.provincia, r.escala);