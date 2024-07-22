package main

import (
    "fmt"
)

// Node, Queue, and Tree structures are defined
// They intearact to reach a solution

type Node struct {
    Symb byte
    Freq   int
    Left, Right *Node
}

type Queue []*Node

type Tree struct {
    Root *Node
}

// Link creates links two nodes as children
// Symb is set to 0 and Freq as the sum from they children
// If frequencies are equal, data is sorted by symbol
func (node *Node) Link(a *Node, b *Node) {
    node.Symb = 0;
    node.Freq = a.Freq + b.Freq;
    if a.Freq > b.Freq {
        node.Left = a
        node.Right = b
    } else if a.Freq < b.Freq {
        node.Left = b
        node.Right = a
    } else {
        if a.Symb < b.Symb {
            node.Left = a
            node.Right = b
        } else {
            node.Left = b
            node.Left = a
        }
    }
}

// Creates a binary sorted tree by frecuency
func (tree *Tree) InsertSorted(nd *Node) {
    if tree.Root == nil {
        tree.Root = nd
        return
    }
    var inserted bool
    curr := tree.Root
    // Goind down until find the position
    // for the new node
    for ; ! inserted ; {
        if nd.Freq < curr.Freq {
            if curr.Left == nil {
                curr.Left = nd
                inserted = true
            } else {
                curr = curr.Left
            }
        } else {
            if curr.Right == nil {
                curr.Right = nd
                inserted = true
            } else {
                curr = curr.Right
            }
        }
    }
}

// A frecuency table is computed from an string
// From that table, a tree is created
func (tree *Tree) InsertFromStream(stream []byte) {
    const n = 256
    freqs := [n]int{}
    for i := 0; i < len(stream); i++ {
        freqs[stream[i]]++
    }
    for i := 0; i < n; i++ {
        if freqs[i] != 0 {
            tree.InsertSorted(&Node{byte(i), freqs[i], nil, nil})
        }
    }
}

// Creates a queue from a tree
func (queue *Queue) AppendNode(node *Node) {
    if node == nil {
        fmt.Println("A nil node")
        return
    }
    if node.Left != nil {
        queue.AppendNode(node.Left)
    }
    *queue = append(*queue, node)
    if node.Right != nil {
        queue.AppendNode(node.Right)
    }
}

// Createas a Huffman tree from a priority queue
func (tree *Tree) InsertFromQueue(queue Queue) {
    for i := 0; i < len(queue); {
        a := &Node{queue[i].Symb, queue[i].Freq, nil, nil}
        i++
        if (i == len(queue)) {
            // It's the last element
            if tree.Root == nil {
                tree.Root = a
            } else {
                aux := Node{}
                aux.Link(a, tree.Root)
                tree.Root = &aux;
            }
            break
        }
        b := &Node{queue[i].Symb, queue[i].Freq, nil, nil}
        i++
        c := &Node{}
        c.Link(a, b)
        if tree.Root == nil {
            tree.Root = c
        } else {
            aux := &Node{}
            aux.Link(c, tree.Root)
            tree.Root = aux
        }
    }
}

// Utility to print Huffman codes
func (node *Node) HuffmanCode(seq string) {
    if node.Left != nil {
        node.Left.HuffmanCode(seq + "0")
    }
    if node.Left == nil && node.Right == nil {
        fmt.Println(node.Symb, string(node.Symb), node.Freq, seq)
    }
    if node.Right != nil {
        node.Right.HuffmanCode(seq + "1")
    }
}

// The Huffman sequence
func Huffman(fragment string) {
    stream := []byte(fragment)
    tree := Tree{}
    tree.InsertFromStream(stream)
    queue := Queue{}
    queue.AppendNode(tree.Root)
    huff := Tree{}
    huff.InsertFromQueue(queue)
    huff.Root.HuffmanCode("")
}

func main() {
    fragment := "ACCEBFFFFAAXXBLKE"
    fmt.Println(fragment)
    Huffman(fragment)
}
