package main

import (
    "fmt"
    "testing"
)

func TestNodeLink(t *testing.T) {
    a := Node{65, 5, nil, nil}
    b := Node{67, 2, nil, nil}
    c := Node{}
    c.Link(&a, &b)
    if c.Symb != 0 {
        t.Errorf("node link : symbol assignation failed")        
    } else if c.Freq != 7 {
        t.Errorf("node link : sum of frequencies failed")
    } else if c.Left != &a {
        t.Errorf("node link : Left assignment failed")
    } else if c.Right != &b {
        t.Errorf("node link : Right assigment failed")
    }
}

func TestNodeInsertSorted(t *testing.T) {
    a := Node{65, 5, nil, nil}
    b := Node{67, 2, nil, nil}
    c := Node{67, 7, nil, nil}
    d := Node{67, 3, nil, nil}
    tree := Tree{}
    tree.InsertSorted(&a)
    tree.InsertSorted(&b)
    tree.InsertSorted(&c)
    tree.InsertSorted(&d)
    if tree.Root != &a {
        t.Errorf("tree insert : failed root assignment")
    }
    if tree.Root.Left != &b {
        t.Errorf("tree insert: failed to add left side")
    }
    if tree.Root.Right != &c {
        t.Errorf("tree insert: failed to add right side")
    }
    if tree.Root.Left.Right != &d {
        t.Errorf("tree insert: failed to add subnode")
    }
}

func TestQueueFromNode(t *testing.T) {
    a := Node{65, 5, nil, nil}
    b := Node{67, 2, nil, nil}
    c := Node{67, 7, nil, nil}
    d := Node{67, 3, nil, nil}
    tree := Tree{}
    tree.InsertSorted(&a)
    tree.InsertSorted(&b)
    tree.InsertSorted(&c)
    tree.InsertSorted(&d)
    queue := Queue{}
    queue.AppendNode(tree.Root)
    if queue[0].Freq != 2 {
        t.Errorf("queue from tree: failed %d", queue[0].Freq)
    }
    if queue[1].Freq != 3 {
        t.Errorf("queue from tree: failed %d", queue[0].Freq)
    }
    if queue[3].Freq != 7 {
        t.Errorf("queue from tree: failed %d", queue[0].Freq)
    }
    if len(queue) != 4 {
        t.Errorf("queue from tree: failed with queue size")
    }
}

func TestNodeInsertFromStream(t *testing.T) {
    stream := []byte{65, 65, 11, 33, 33}
    tree := Tree{}
    tree.InsertFromStream(stream)
    if tree.Root.Symb != 11 {
        t.Errorf("tree insert from stream: failed %d", tree.Root.Symb)
    }
    if tree.Root.Right.Symb != 33 {
        t.Errorf("tree insert from stream: failed %d", tree.Root.Right.Symb)
    }
    if tree.Root.Right.Right.Symb != 65 {
        t.Errorf("tree insert from stream: failed %d", tree.Root.Right.Right.Symb)
    }
    if tree.Root.Left != nil {
        t.Errorf("tree insert from stream: failed in left")
    }
}

func TestTreeInsertFromQueue(t *testing.T) {
    stream := []byte{65, 65, 11, 21, 21, 21, 21, 33, 33, 33}
    tree := Tree{}
    tree.InsertFromStream(stream)
    queue := Queue{}
    queue.AppendNode(tree.Root)
    huff := Tree{}
    huff.InsertFromQueue(queue)
    if huff.Root.Left.Left.Symb != 21 {
        t.Errorf("tree insert from queue: failed %d", tree.Root.Left.Left.Symb)
    }
    if huff.Root.Right.Right.Symb != 11 {
        t.Errorf("tree insert from queue: failed %d", tree.Root.Right.Right.Symb)
    }
}

func TestHuffmanCode(t *testing.T) {
    stream := []byte("ACCEBFFFFAAXXBLKE")
    fmt.Println(stream)
    tree := Tree{}
    tree.InsertFromStream(stream)
    queue := Queue{}
    queue.AppendNode(tree.Root)
    huff := Tree{}
    huff.InsertFromQueue(queue)
    huff.Root.HuffmanCode("")
}
