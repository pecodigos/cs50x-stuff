SELECT name FROM people
JOIN stars ON people.id = stars.person_id WHERE people.name != 'Kevin Bacon' AND stars.movie_id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958));
