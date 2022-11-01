SELECT m.title AS title
  FROM movies AS m,
       stars AS s,
       people AS p
 WHERE p.name = "Johnny Depp"
   AND p.id = s.person_id
   AND s.movie_id = m.id

   INTERSECT

SELECT m.title AS title
  FROM movies AS m,
       stars AS s,
       people AS p
 WHERE p.name = "Helena Bonham Carter"
   AND p.id = s.person_id
   AND s.movie_id = m.id;