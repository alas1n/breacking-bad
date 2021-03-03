from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for, Response
)
from werkzeug.exceptions import abort

from flaskr.auth import login_required
from flaskr.db import get_db

from flask import Flask, jsonify



bp = Blueprint('blog', __name__)

# Index
@bp.route('/')
def index():
    db = get_db()
    posts = db.execute(
        'SELECT p.id, title, body, created, author_id, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' ORDER BY created DESC'
    ).fetchall()
    return render_template('blog/index.html', posts=posts)


# Create
@bp.route('/create', methods=('GET', 'POST'))
@login_required
def create():
    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if not title:
            error = 'Title is required.'

        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'INSERT INTO post (title, body, author_id)'
                ' VALUES (?, ?, ?)',
                (title, body, g.user['id'])
            )
            db.commit()
            # return redirect(url_for('blog.index'))

    return render_template('blog/create.html')


# update
def get_post(id, check_author=True):
    post = get_db().execute(
        'SELECT p.id, title, body, created, author_id, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' WHERE p.id = ?',
        (id,)
    ).fetchone()

    if post is None:
        abort(404, "Post id {0} doesn't exist.".format(id))

    if check_author and post['author_id'] != g.user['id']:
        abort(403)

    return post

@bp.route('/<int:id>/update', methods=('GET', 'POST'))
@login_required
def update(id):
    post = get_post(id)

    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if not title:
            error = 'Title is required.'

        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'UPDATE post SET title = ?, body = ?'
                ' WHERE id = ?',
                (title, body, id)
            )
            db.commit()
            return redirect(url_for('blog.index'))

    return render_template('blog/update.html', post=post)


# delete
@bp.route('/<int:id>/delete', methods=('POST',))
@login_required
def delete(id):
    get_post(id)
    db = get_db()
    db.execute('DELETE FROM post WHERE id = ?', (id,))
    db.commit()
    return redirect(url_for('blog.index'))





# getpost1
def get_post1(id):
    post = get_db().execute(
        'SELECT p.id, title, body, created, author_id, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' WHERE p.id = ?',
        (id,)
    ).fetchone()

    return post

def body_to_1(id):
  post = get_post1(id)
  number = int(post[1])
  number = number + 1
  number = str(number)
  db = get_db()
  db.execute(
    'UPDATE post SET title = ?, body = ?'
    ' WHERE id = ?',
    (number, "2", id)
    )
  db.commit()
  return 'done'

# def body_to_0(id):
#   post = get_post1(id)
#   db = get_db()
#   db.execute(
#     'UPDATE post SET title = ?, body = ?'
#     ' WHERE id = ?',
#     ('10', '0', id)
#     )
#   db.commit()
#   return 'done'


# # MINE GET
# @bp.route('/get', methods=('HEAD',))
# def mine():
#   post = get_post1(1)
#   body_to_0(1)
#   # return jsonify({"hello":'done'})
#   return post[2]


# MINE POST  
@bp.route('/send', methods=('GET','HEAD'))
def mine1():
  body_to_1(1)
  # post = get_post1(1)
  # return "hellow"
  return None


  # MINE POST  
@bp.route('/receive', methods=('GET','HEAD'))
def mine2():
  post = get_post1(1)
  response = Response()
  response.headers["value"] = post[1]
  return response