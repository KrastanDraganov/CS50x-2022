SELECT p.name AS name
  FROM people AS p,
       stars AS s,
       movies AS m
  WHERE p.id = s.person_id
    AND s.movie_id = m.id
    AND m.title = "Toy Story";