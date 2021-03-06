/*
 * FileType.java
 *
 * Copyright (C) 2009-12 by RStudio, Inc.
 *
 * This program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */
package org.rstudio.studio.client.common.filetypes;

import org.rstudio.core.client.FilePosition;
import org.rstudio.core.client.files.FileSystemItem;
import org.rstudio.studio.client.application.events.EventBus;

import java.util.ArrayList;

public abstract class FileType
{
   static ArrayList<FileType> ALL_FILE_TYPES = new ArrayList<FileType>();

   protected FileType(String id)
   {
      id_ = id;
      ALL_FILE_TYPES.add(this);
   }

   public String getTypeId()
   {
      return id_;
   }

   public void openFile(FileSystemItem file, 
                        FilePosition position,
                        boolean highlightLine,
                        EventBus eventBus)
   {
      openFile(file, null, false, eventBus);
   }
   
   protected abstract void openFile(FileSystemItem file, EventBus eventBus);
   
   private final String id_;
}
