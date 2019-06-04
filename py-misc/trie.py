import math
import os
import random
import re
import sys

class Trie:
    def __init__(self):
        self.VALUE = '_v'
        self._trie = {}
    def _iter_rec(self, node,
            key,        # collect current key
            allkeys):   # collect all keys
        if node is None or len(node) == 0:
            return
        if self.VALUE in node:
            allkeys.append(key)
        for c in node:
            if c != self.VALUE:
                self._iter_rec(node[c], key + c, allkeys)
    def __iter__(self):
        keys = []
        self._iter_rec(self._trie, '', keys)
        for k in keys:
            yield k
    def __str__(self):
        return '    keys: {}\n    {}'.format(list(iter(self)), self._trie)
    def _validatekey(self, key):
        if not isinstance(key, str):
            raise RuntimeError()
    def getnode(self, key):
        self._validatekey(key)
        curmap = self._trie
        node = None
        for i,c in enumerate(key):
            if c not in curmap:
                return None
            curmap = curmap[c]
            if i == len(key) - 1:
                node = curmap
        return node
    def get(self, key):
        node = self.getnode(key)
        if node is not None:
            val = node[self.VALUE]
            # print(f'found: {key}={val}')
            return val
        # print(f'not found: key={key}')
        return None
    def list(self, prefix):
        self._validatekey(key)
        curmap = self._trie
        val = None
        l = []
        for i,c in enumerate(key):
            if c in curmap:
                curmap = curmap[c]
                if i == len(key) - 1:
                    val = curmap[self.VALUE]
        if val is None:
            print(f'not found: i={i} key={key}')
        else:
            print(f'found: {key}={val}')
    def put(self, key, val):
        self._validatekey(key)
        curmap = self._trie
        for i,c in enumerate(key):
            curmap = curmap.setdefault(c, {})
            if i == len(key) - 1:
                curmap[self.VALUE] = val
    def _nodelen(self, node):
        if self.VALUE in node:
            return len(node) - 1
        return len(node)
    def delete(self, key):
        node = self.getnode(key)
        if node is not None:
            val = node.pop(self.VALUE)
            return
        print(f'delete(): not found: key={key}')


# https://github.com/bdimmick/python-trie/blob/master/trie_unittest.py
import unittest
class TestTrie(unittest.TestCase):
    def setUp(self):
        self.trie = Trie()

    def _square_brackets(self, key):
        return self.trie[key]

    def test_basicAssignment(self):
        self.trie["Foo"] = True
        self.assertTrue(self.trie["Foo"])
        self.assertRaises(KeyError, self._square_brackets, "Food")
        self.assertEquals(1, len(self.trie))
        self.assertEquals(3, self.trie.nodeCount())
        self.assertTrue("Foo" in self.trie)
        self.trie["Bar"] = None
        self.assertTrue("Bar" in self.trie)

    def test_basicRemoval(self):
        self.trie["Foo"] = True
        self.assertTrue(self.trie["Foo"])
        del self.trie["Foo"]
        self.assertRaises(KeyError, self._square_brackets, "Foo")
        self.assertEquals(0, len(self.trie))
        self.assertEquals(0, self.trie.nodeCount())
        self.assertFalse("Foo" in self.trie)

    def test_MixedTypes(self):
        self.trie["Foo"] = True
        self.trie[[1, 2, 3]] = True
        self.assertTrue(self.trie["Foo"])
        self.assertTrue(self.trie[[1, 2, 3]])
        self.assertTrue([1, 2, 3] in self.trie)
        self.assertTrue("Foo" in self.trie)
        del self.trie[[1, 2, 3]]
        self.assertFalse([1, 2, 3] in self.trie)

    def test_Iteration(self):
        self.trie["Foo"] = True
        self.trie["Bar"] = True
        self.trie["Grok"] = True
        for k in self.trie:
            self.assertTrue(k in self.trie)
            self.assertTrue(self.trie[k])

    def test_Addition(self):
        self.trie["Foo"] = True
        t2 = Trie()
        t2["Food"] = True
        t3 = t2 + self.trie
        self.assertTrue("Foo" in self.trie)
        self.assertFalse("Food" in self.trie)
        self.assertTrue("Food" in t2)
        self.assertFalse("Foo" in t2)
        self.assertTrue("Foo" in t3)
        self.assertTrue("Food" in t3)

    def test_Subtraction(self):
        self.trie["Food"] = True
        self.trie["Foo"] = True
        t2 = Trie()
        t2["Food"] = True
        t3 = self.trie - t2
        t4 = t2 - self.trie
        self.assertTrue("Food" in self.trie)
        self.assertTrue("Foo" in self.trie)
        self.assertTrue("Food" in t2)
        self.assertTrue("Foo" in t3)
        self.assertFalse("Food" in t3)
        self.assertFalse("Foo" in t4)
        self.assertFalse("Food" in t4)

    def test_SelfAdd(self):
        self.trie["Foo"] = True
        t2 = Trie()
        t2["Food"] = True
        self.assertTrue("Foo" in self.trie)
        self.assertFalse("Food" in self.trie)
        self.assertTrue("Food" in t2)
        self.assertFalse("Foo" in t2)
        self.trie += t2
        self.assertTrue("Foo" in self.trie)
        self.assertTrue("Food" in self.trie)

    def test_SelfSub(self):
        self.trie["Foo"] = True
        self.trie["Food"] = True
        t2 = Trie()
        t2["Food"] = True
        self.assertTrue("Food" in self.trie)
        self.assertTrue("Foo" in self.trie)
        self.assertTrue("Food" in t2)
        self.trie -= t2
        self.assertFalse("Food" in self.trie)
        self.assertTrue("Foo" in self.trie)
        self.assertTrue("Food" in t2)

    def test_SelfGet(self):
        self.trie["Foo"] = True
        self.assertTrue(self.trie["Foo"])
        self.assertRaises(KeyError, self._square_brackets, "Food")
        self.assertEquals("Bar", self.trie.get("Food", "Bar"))
        self.assertEquals("Bar", self.trie.get("Food", default="Bar"))
        self.assertTrue(self.trie.get("Foo"))
        self.assertTrue(self.trie.get("Food") is None)

    def test_KeysByPrefix(self):
        self.trie["Foo"] = True
        self.trie["Food"] = True
        self.trie["Eggs"] = True
        kset = self.trie.keys()
        self.assertTrue("Foo" in kset)
        self.assertTrue("Food" in kset)
        self.assertTrue("Eggs" in kset)        
        kset = self.trie.keys("Foo")        
        self.assertTrue("Foo" in kset)
        self.assertTrue("Food" in kset)
        kset = self.trie.keys("Ox")
        self.assertEquals(0, len(kset))

if __name__ == '__main__':
    t = Trie()
    t.put('foo', 'the value of foo')
    t.put('foo2', 'foo2 is much different')
    t.put('bar', 'whoa')
    t.get('foo')
    t.get('foo2')
    t.get('bar')
    t.get('baz')
    t.delete('baz')

    print('before delete:\n{}'.format(t))
    t.delete('foo')
    print('after delete:\n{}'.format(t))

    for k in t:
        t.delete(k)
    print('after clear:\n{}'.format(t))
    # unittest.main()
