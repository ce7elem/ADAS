package main

import (
	"bufio"
	"log"
	"os"

	"strings"
	"regexp"
	"path/filepath"
)

func main() {

	root := os.Args[1:]

	var files []string
	var readmeFiles []string

	wd,err := os.Getwd()
	if err != nil {
		panic(err)
	}
	indexdir := filepath.Dir(wd)

	// scanning src folder for source code files
	err = filepath.Walk(root[0], func(path string, info os.FileInfo, err error) error {
		if isSourceCode(path) {
			files = append(files, path)
		}
		return nil
	})
	if err != nil {
		panic(err)
	}
	for _, file := range files {
		log.Print(" + ", file)
	}

	// parsing each source file to find comments
	for i, path := range files {
		dir, filename := filepath.Split(path)
		if err != nil {
			log.Fatal(err)
		}

		log.Printf("Parsing file %d/%d : %s in %s\n", i+1, len(files), filename, dir)

		for {
			if strings.Count( strings.ReplaceAll(dir, indexdir, ""), "/") > 1 {
				dir = filepath.Clean(dir+"/..")
			} else {
				break;
			}
		}
		if dir == "" {
			dir = "."
		}
		dir = dir+"/"

		
		file, err := os.Open(path)
		if err != nil {
			log.Fatal(err)
		}
		defer file.Close()

		print := false
		var re = regexp.MustCompile(`(\s\[\n])*(/+|\**)*(\s\[\n])*`)

		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line := scanner.Text()
			if strings.Contains(line, "/**") { 
				print = true
			}

			if strings.Contains(line, "*/") { 
				print = false
			}


			// printing the md to the correspondant README.md
			if print {

				f, err := os.OpenFile(dir+"README.md", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)

				if err != nil {
					log.Fatal(err)
				}
				if _, err := f.WriteString(re.ReplaceAllString(line, ``)+"\n"); err != nil {
					log.Fatal(err)
				}

				if err := f.Close(); err != nil {
					log.Fatal(err)
				}

				readmeFiles = pushIfNotExists(readmeFiles, filepath.Clean(strings.ReplaceAll(dir, indexdir, "")))

			}
		}

		if err := scanner.Err(); err != nil {
			log.Fatal(err)
		}

	}

	// create routes config file for docute (a bit dirty but it should work)	
	if err := os.Remove(indexdir+"/Doc/pages.json"); err != nil {
		log.Fatal(err)
	}
	f, err := os.OpenFile(indexdir+"/Doc/pages.json", os.O_RDWR|os.O_CREATE, 0755)

	if _, err := f.WriteString("["); err != nil {
		log.Fatal(err)
	}
	for index, i := range readmeFiles {
		if _, err := f.WriteString(`{
				"title": "`+func() string { if filepath.Base(i) == "." { return "main" } else { return filepath.Base(i) } }()+`",
				"link": "`+filepath.Clean("/src/"+i)+`/"
			}`); err != nil {
			log.Fatal(err)
		}
		if (index < len(readmeFiles)-1) {
			if _, err := f.WriteString(`,`); err != nil {
				log.Fatal(err)
			}
		}
	}
	if _, err := f.WriteString("]"); err != nil {
		log.Fatal(err)
	}

	if err := f.Close(); err != nil {
		log.Fatal(err)
	}

}



func isSourceCode(path string) bool {
	switch filepath.Ext(path) {
	case
		".c",
		".h":
		return true
	}
	return false
}


func pushIfNotExists(slice []string, i string) []string {
	for _, ele := range slice {
		if ele == i {
			return slice
		}
	}
	return append(slice, i)
}