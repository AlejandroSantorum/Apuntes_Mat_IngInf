#!/usr/bin/env python
# encoding: ascii
###############################################################################
# sagews2ipynb Convert a SageMathCloud worksheet into an iPython notebook.
# This is useful because iPython notebooks are the only format
# that works both for pushing/pulling files from sagemathcloud.
#
# Mostly a fork of sagews2pdf.py by William Stein.
#
# Original copyright follows:
#
# SageMathCloud: A collaborative web-based interface to Sage, IPython, LaTeX and the Terminal.
#
#    Copyright (C) 2014, William Stein
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################



"""
This is a modified sagews2pdf.py so that it outputs an iPython notebook.

Original copyright follows.


Copyright (c) 2014, William Stein
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CONTRIBUTORS:

  - William Stein (maintainer and initial author)
  - Cedric Sodhi  - internationalization and bug fixes
  - Tomas Kalvoda - internationalization

"""

MARKERS = {'cell':u"\uFE20", 'output':u"\uFE21"}

# TODO: this needs to use salvus.project_info() or an environment variable or something!
site = 'https://cloud.sagemath.com'
# TODO: this too needs customizing.
kernelspec={
    "display_name": "Sage 6.6",
    "language": "python",
    "name": "sage_6_6"
}
# metadata= {
#   "kernelspec": {
#    "display_name": "Python 2",
#    "language": "python",
#    "name": "python2"
#   },
#   "language_info": {
#    "codemirror_mode": {
#     "name": "ipython",
#     "version": 2
#    },
#    "file_extension": ".py",
#    "mimetype": "text/x-python",
#    "name": "python",
#    "nbconvert_exporter": "python",
#    "pygments_lexer": "ipython2",
#    "version": "2.7.8"
#   }
#  }

DEBUG=False
def dprint(s):
    if DEBUG:
        print s

xxcount=0
def xcount():
    """docstring for xcount"""
    global xxcount
    return xxcount
def next_xcount():
    """docstring for next_xcount"""
    global xxcount
    xxcount+=1
    return xxcount
def prev_xcount():
    """docstring for next_xcount"""
    global xxcount
    xxcount-=1
    return xxcount



import argparse, base64, cPickle, json, os, shutil, sys, textwrap, HTMLParser, tempfile, urllib
from uuid import uuid4
import StringIO

def escape_path(s):
    # see http://stackoverflow.com/questions/946170/equivalent-javascript-functions-for-pythons-urllib-quote-and-urllib-unquote
    s = urllib.quote(unicode(s).encode('utf-8'), safe='~@#$&()*!+=:;,.?/\'')
    return s.replace('#','%23').replace("?",'%3F')

def wrap(s, c=90):
    return '\n'.join(['\n'.join(textwrap.wrap(x, c)) for x in s.splitlines()])
    
def outsplit(s):
    ss=s.splitlines()
    if len(ss)>1:
        return [t+'\n' for t in ss[:-1]]+ss[-1:]
    else: 
        return ss
    
## Removed lots of code here.

class Cell(object):
    def __init__(self, s):
        self.raw = s
        v = s.split('\n' + MARKERS['output'])
        if len(v) > 0:
            w = v[0].split(MARKERS['cell']+'\n')
            n = w[0].lstrip(MARKERS['cell'])
            self.input_uuid = n[:36]
            self.input_codes = n[36:]
            if len(w) > 1:
                self.input = w[1]
            else:
                self.input = ''
        else:
            self.input_uuid = self.input = ''
        
        if len(v) > 1:
            w = v[1].strip().strip(MARKERS["output"]).split(MARKERS['output'])
            self.output_uuid = w[0] if len(w) > 0 else ''
            self.output = []
            for x in w[1:]:
               # x = x.strip()
                if x:
                    try:
                        self.output.append(json.loads(x))
                    except ValueError:
                        try:
                            print "**WARNING:** Unable to de-json '%s'"%x
                        except:
                            print "Unable to de-json some output"
        else:
            self.output = self.output_uuid = ''
        
        #import pdb;pdb.set_trace()
        
        if self.input:
            for out in self.output[:]:
                if "html" in out and "%html" not in self.input:
                    self.output.remove(out)


    def dict_list(self):
        """
        Return a dict representation of this cell for later
        json serialization
        """
        self._jdict=[]
        self.do_cell_input()
        self.do_cell_output()
        return self._jdict

    def do_cell_input(self):
        """Return a dict representation of self."""
        d = {
                'cell_type': 'code',
                'execution_count': next_xcount(),
                'metadata': {'collapsed': False},
                'source': outsplit(self.input.strip()),
                'outputs': []
            }
        if 'i' in self.input_codes:   # hidden input
            # if it's hidden, skip it.
            dprint("Ignoring cell "+self.input_uuid)
            return

        dprint("Processed cell "+self.input_uuid+" with codes "+self.input_uuid)
        self._jdict.append(d)


    def do_cell_output(self):
        
        if 'o' in self.input_codes:  # hide output
            dprint("Ignoring output of cell "+self.input_uuid)
            return # nothing to see here, move on
            
        for x in self.output:
            if 'stdout' in x:
                d = {
                    'output_type': 'execute_result',
                    'metadata': {},
                    'execution_count': xcount(),
                    'data': {
                        'text/plain': outsplit(wrap(x['stdout']))
                    }
                }
                self._jdict[0]['outputs'].append(d)
                dprint("Stdout output")
                continue

            if 'stderr' in x:
                d = {
                    'output_type': 'stream',
                    'name': 'stderr',
                    'text': outsplit(wrap(x['stderr']))
                }
                self._jdict[0]['outputs'].append(d)
                dprint("Stderr output")
                continue

            if 'code' in x:
                # TODO: for now ignoring that not all code is Python...
                # Should this be in a cell by itself?
                d = {
                    'output_type': 'execute_result',
                    'metadata': {},
                    'execution_count': xcount(),
                    'data': {
                        'text/plain': outsplit(wrap(x['code']['source']))
                    }
                }
                self._jdict[0]['outputs'].append(d)
                dprint("Code output")
                continue

#            if 'html' in x:
#                d = {
#                    'output_type': 'execute_result',
#                    'data': {
#                        'text/html': [x['html']]
#                    },
#                    'metadata': {},
#                    'execution_count': xcount()
#                }
#                #self._jdict[0]['outputs'].append(d)
#                self._jdict=[d]
#                dprint("HTML output")
#                continue

            if 'html' in x:
                # for now, just read HTML in as markdown cell, since Jupyter
                # doesn't seem to handle HTML cells in the form above.
                d={
                    'cell_type': 'markdown',
                    'metadata': {},
                    'source': [x['html']]
                }
                # Overwrite the original cell and move on
                prev_xcount()
                self._jdict=[d]
                dprint("Markdown output, overwriting original cell and moving on")
                return

            if 'md' in x:
                d={
                    'cell_type': 'markdown',
                    'metadata': {},
                    'source': [x['md']]
                }
                # Overwrite the original cell and move on
                prev_xcount()
                self._jdict=[d]
                dprint("Markdown output, overwriting original cell and moving on")
                return

            if 'interact' in x:
                dprint("Interact output, moving on")
                continue

            if 'tex' in x:
                val = x['tex']
                s="$$%s$$"%val['tex'] if 'display' in val else "$%s$"%val['tex']
                d = {
                    'output_type': 'execute_result',
                    'data': {
                        'text/latex': [s]
                    },
                    'execution_count': xcount(),
                    'metadata': {}
                }
                self._jdict[0]['outputs'].append(d)
                dprint("tex output")
                continue

            if 'file' in x:
                dprint("File output, keep posted...")
                val = x['file']
                #
                if 'url' in val:
                    target = val['url']
                    filename = os.path.split(target)[-1]
                else:
                    filename = os.path.split(val['filename'])[-1]
                    target = "%s/blobs/%s?uuid=%s"%(site, escape_path(filename), val['uuid'])

                try:
                    file_content=StringIO.StringIO(urllib.urlopen(target).read())
                except:
                    print "Could not read %s, skipping."%target
                    return

                base, ext = os.path.splitext(filename)
                ext = ext.lower()[1:]
                if ext in ['svg']:
                    dprint("... SVG")
                    o=file_content.getvalue()
                    s=o.lower()
                    # put in try-except since this might be running on a local
                    # machine, and then *s* will contain something like "blob
                    # <UID> not found" instead of containing SVG code
                    try:
                        p=s.index("<svg")
                        q=s.index("</svg>")+6
                        d = {
                            'output_type': 'execute_result',
                            'execution_count': xcount(),
                            'metadata': {'isolated': True},
                            'data': {
                                'image/svg+xml': outsplit(o[p:q]),
                                'text/plain': ["<IPython.core.display.SVG object>"],
                            }
                        }
                        self._jdict[0]['outputs'].append(d)
                    except ValueError:
                        pass

                    continue

                elif ext in ['jpg', 'png', 'eps', 'pdf']:
                    dprint("..."+ext)
                    d = {
                        'output_type': 'execute_result',
                        'execution_count': xcount(),
                        'metadata': {},
                        'data': {
                            'image/'+ext: [base64.b64encode(file_content.getvalue())]
                        }
                    }
                    self._jdict[0]['outputs'].append(d)
                    continue

                else:
                    dprint("Fallback to link")
                    d = {
                        'output_type': 'execute_result',
                        'execution_count': xcount(),
                        'metadata': {},
                        'data': {
                            'text/html': ['<a href="%s">%s</a>'%(target,target)]
                        }
                    }
                    self._jdict[0]['outputs'].append(d)
                    continue

            else:
                dprint("Fallback to plain text")
                d = {
                    'output_type': 'execute_result',
                    'execution_count': xcount(),
                    'metadata': {'collapsed': False},
                    'data': {
                        'text/plain': [str(x)]
                    }
                }
                self._jdict[0]['outputs'].append(d)
                continue



class Worksheet(object):
    def __init__(self, filename=None, s=None):
        """
        The worksheet defined by the given filename or UTF unicode string s.
        """
        self._default_title = ''
        if filename:
            self._filename = os.path.abspath(filename)
        else:
            self._filename = None
        if filename is not None:
            self._default_title = filename
            self._init_from(open(filename).read().decode('utf8'))
        elif s is not None:
            self._init_from(s)
        else:
            raise ValueError("filename or s must be defined")

    def _init_from(self, s):
        self._cells = [Cell(x) for x in s.split('\n'+MARKERS['cell'])]

    def __getitem__(self, i):
        return self._cells[i]

    def __len__(self):
        return len(self._cells)

    def json(self, filename, title, author, date):
        dlist=[]
        for C in self._cells:
            dlist += C.dict_list()
        d={
            'nbformat': 4,
            'nbformat_minor': 0,
            'cells': dlist,
            'metadata': {
                'kernelspec': kernelspec
            }
        }
        return json.dumps(d, indent=1)

def sagews_to_jdict(filename, title='', author='', date='', outfile='', contents=True, remove_tmpdir=True):
    base = os.path.splitext(filename)[0]
    if not outfile:
        nb = base + ".ipynb"
    else:
        nb = outfile
    print "converting: %s --> %s"%(filename, nb)
    W = Worksheet(filename)
    s=W.json(filename, title, author, date)
    open(nb,'w').write(s.encode('utf8'))


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="convert a sagews worksheet to a pdf file via latex")
    parser.add_argument("filename", help="name of sagews file (required)", type=str)
    parser.add_argument("--author", dest="author", help="author name for printout", type=str, default="")
    parser.add_argument("--title", dest="title", help="title for printout", type=str, default="")
    parser.add_argument("--date", dest="date", help="date for printout", type=str, default="")
    parser.add_argument("--contents", dest="contents", help="include a table of contents 'true' or 'false' (default: 'true')", type=str, default='true')
    parser.add_argument("--outfile", dest="outfile", help="output filename (defaults to input file with sagews replaced by pdf)", type=str, default="")
    parser.add_argument("--remove_tmpdir", dest="remove_tmpdir", help="if 'false' do not delete the temporary LaTeX files and print name of temporary directory (default: 'true')", type=str, default='true')
    parser.add_argument("--extra_data_file", dest="extra_data_file", help="JSON format file that contains extra data useful in printing this worksheet, e.g., 3d plots", type=str, default='')

    args = parser.parse_args()
    args.contents = args.contents == 'true'
    args.remove_tmpdir = args.remove_tmpdir == 'true'

    if args.extra_data_file:
        import json
        extra_data = json.loads(open(args.extra_data_file).read())
    else:
        extra_data = {}

    sagews_to_jdict(args.filename, title=args.title.decode('utf8'),
                  author=args.author.decode('utf8'), outfile=args.outfile,
                  date=args.date, contents=args.contents, remove_tmpdir=args.remove_tmpdir)
